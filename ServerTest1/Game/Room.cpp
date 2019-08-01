#include "../stdafx.h"
#include "Room.h"

using namespace std;

Room::Room(const int _roomNum) :m_roomNum(_roomNum), m_lobby(nullptr), m_play(nullptr), m_entry(ENTRYSTATE::ENTRY_PERMIT)
{
	m_lobby = std::make_unique<Lobby>();
	m_play = std::make_unique<Play>();
}

Room::Room(const int _roomNum, Player _p) :m_roomNum(_roomNum), m_lobby(nullptr), m_play(nullptr), m_entry(ENTRYSTATE::ENTRY_PERMIT)
{
	m_lobby = make_unique<Lobby>();
	m_play = make_unique<Play>();

	m_playerList.push_back(_p);
}

Room::~Room()
{
}

/// <summary>
/// 受信
/// </summary>
void Room::Receive()
{
	// 個人の処理
	for (list<Player>::iterator it = m_playerList.begin(); it != m_playerList.end(); it++)
	{
		int recvSize = 0;
		

		//	通信
		RECV_CONNECTION state = ServerNet::GetInstans()->Recv((it)->socket, m_data, sizeof(m_data), &recvSize);
		
		// 通信が成功したら
		if (state == RECV_CONNECTION::RECV_SUCCESS)
		{
			// 送られたデータを戻す
			Player p;
			memcpy(&p, m_data, sizeof(Player));

			// ルームリストのプレイヤーの更新
			(*it) = p;

			// シーンがPlayの時
			if (it->scene == Data::SCENE::PLAY)
			{
				// 接続が切れたか確認
				for (list<Player>::iterator ver = m_playerList.begin(); ver != m_playerList.end(); ver++)
				{
					// 回線が切れたら
					if (m_play->SceneFlag(*ver) == -1)
					{
						// デリートリストに追加
 						m_delList.push_back(*ver);
						// 接続が切れたことを報告
						m_sendList.push_back(*ver);
 						continue;
					}
				}
				// ルームに人がいなくなったら
				if (m_playerList.size() == 0)
				{
					cout << "ルーム" << m_roomNum << " が空になりました。ルームを削除します" << endl;
					cout << "ルーム" << m_roomNum << " を削除します" << endl;
					// 部屋を削除する
					m_entry = ENTRYSTATE::DELETE_ROOM;
				}
			}
			// シーンがLobbyの時　
			else if (it->scene == Data::SCENE::LOBBY)
			{
				if (it->nextScene != Data::SCENE::NON) { it->nextScene = Data::SCENE::NON; }

				// 今ロビーにいる人を送る
				for each(Player tmp in m_playerList) { m_sendList.push_back(tmp); }
				
				// 全員同時に処理するとき
				// 全員のOK確認がとれたならシーン変更(chack  :: -1 / 切断　, 0 / 何もしない　, 1 / 次のシーンへ )
				int chack = 0;
				for (list<Player>::iterator ver = m_playerList.begin(); ver != m_playerList.end(); ver++)
				{
					chack = m_lobby->SceneFlag((*ver));
					// 戻るを選択したら
					if (chack == -1)
					{
						// デリートリストに追加
						m_delList.push_back(*ver);
						continue;
					}
					else if (chack == 0) { break; }
				}
				// ゲーム開始
				if (chack == 1)
				{
					// 送るリストを空に
					m_sendList.clear();

					// プレイシーンに移行してもいいと全員に許可を出す
					if (m_playerList.size() > 1)
					{
						for (list<Player>::iterator tmp = m_playerList.begin(); tmp != m_playerList.end(); tmp++)
						{
							tmp->nextScene = Data::SCENE::PLAY;
							m_sendList.push_back(*tmp);
						}
					}

					// 入室制限
					m_entry = ENTRYSTATE::ENTRY_PERMIT;

					cout << "ルーム" << m_roomNum << " がPlaySceneになりました。" << endl;
					cout << "ルーム" << m_roomNum << " の入室を制限します" << endl;

				}

				// ルームに誰もいなくなったら
				if (m_playerList.size() == 0)
				{
					cout << "ルーム" << m_roomNum << " が空になりました。ルームを削除します" << endl;
					cout << "ルーム" << m_roomNum << " を削除します" << endl;
					m_entry = ENTRYSTATE::DELETE_ROOM;
				}
			}
			// シーンがResultの時
			else if (it->scene == Data::SCENE::RESULT)
			{
				// 接続が切れたか確認
				for (list<Player>::iterator ver = m_playerList.begin(); ver != m_playerList.end(); ver++)
				{
					// 回線が切れたら
					if (m_play->SceneFlag(*ver) == -1)
					{
						// デリートリストに追加
						m_delList.push_back(*ver);
						// 接続が切れたことを報告
						m_sendList.push_back(*ver);
						continue;
					}
				}
				// ルームに人がいなくなったら
				if (m_playerList.size() == 0)
				{
					cout << "ルーム" << m_roomNum << " が空になりました。ルームを削除します" << endl;
					cout << "ルーム" << m_roomNum << " を削除します" << endl;
					// 部屋を削除する
					m_entry = ENTRYSTATE::DELETE_ROOM;
				}
			}
		}
		// 接続が切れた人を削除リストに登録
		else if (state == RECV_CONNECTION::RECV_FAILURE)
		{
			cout << "ルーム" << m_roomNum << "から " << it->socket << " が退出しました" << endl;
			it->scene = Data::SCENE::LOGOUT;
			m_sendList.push_back(*it);
			m_delList.push_back(*it);
		}
	}
}

void Room::Execution()
{
	// ルームからの削除処理
	if (m_delList.size() != 0)
	{
		for each (Player var in m_delList)
		{
			for (list<Player>::iterator itr = m_playerList.begin(); itr != m_playerList.end();)
			{
				if (var.socket == itr->socket)
				{
					cout << itr->socket << " が切断しました" << endl;
					itr = m_playerList.erase(itr);
					break;
				}
				itr++;
			}
		}
		// ルーム内に人がいなくなったら
		if (m_entry == ENTRYSTATE::NO_ENTRY && m_playerList.size() < 1)
		{
			cout << "ルーム" << m_roomNum << " は入室可能です。" << endl;
			m_entry = ENTRYSTATE::ENTRY_PERMIT;
		}
		m_delList.clear();
	}

	// あたり判定などを計算
	for (list<Player>::iterator it = m_playerList.begin(); it != m_playerList.end(); it++)
	{
		if (it->scene == Data::SCENE::PLAY)
		{
			for (list<Player>::iterator tmp = m_playerList.begin(); tmp != m_playerList.end(); tmp++)
			{
				if (it->socket != tmp->socket)
				{
					m_play->Execution(&*it, &*tmp);
				}
			}
			m_sendList.push_back(*it);
		}
	}

	// センドリストに入っていたら
	if (m_sendList.size() != 0)
	{
		// センドリストの中身をルームの中にいる人全員に送る
		for each (Player var in m_sendList)
		{
			
			memcpy(m_data, &var, sizeof(Player));
			
			for (list<Player>::iterator it = m_playerList.begin(); it != m_playerList.end(); ++it)
			{

				ServerNet::GetInstans()->Send((*it).socket, m_data, sizeof(m_data));
			}
		}
		// 送ったらセンドリストを消す
		m_sendList.clear();
	}
}

void Room::PushList(Player _p)
{
	m_playerList.push_back(_p);
}


