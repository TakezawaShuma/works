// ServerTest1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Game/Data.h"
#include "Network\ServerNet.h"

#include "Game/Scenes/Login/LoginScene.h"

//#include "Scenes\Scene.h"

#include "Game\Room.h"

#include <WinSock2.h>
#include <iostream>
#include <list>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

#ifdef _MSC_VER
#define DISABLE_C4996   __pragma(warning(push)) __pragma(warning(disable:4996))
#define ENABLE_C4996    __pragma(warning(pop))
#else
#define DISABLE_C4996
#define ENABLE_C4996
#endif

using namespace std;

bool GetHostIp(void)
{
	int i;
	HOSTENT* IpHost;	// ホスト情報を格納しておく構造体
	IN_ADDR inAddr;		// IPアドレスを格納しておく構造体
	char szBuf[256], szIP[16];		// ホスト名 / IPアドレスを格納しておく配列


	DISABLE_C4996		
									// ローカルマシンのホスト名を取得する
	if (gethostname(szBuf, (int)sizeof(szBuf)) != 0)
	{
		// エラー処理
		cout << "ホスト名を取得出来ませんでした。" << endl;
		// エラーナンバーを取得する
		int err = WSAGetLastError();
		cout << "ERRORNUMBER : " << err << endl;
		Data::ErrorState(err);
		return false;
	}
	cout << "HOST Name : " << szBuf << endl;

	// ホスト情報からIPアドレス等の情報を取得する
	IpHost = gethostbyname(szBuf);
	// エラー処理
	if (IpHost == NULL)
	{
		cout << "IPアドレスを取得できませんでした" << endl;
		// エラーナンバーを取得する
		int err = WSAGetLastError();
		cout << "ERRORNUMBER : " << err << endl;
		Data::ErrorState(err);
		return false;
	}	
	// IPアドレスを取得
	for (i = 0; IpHost->h_addr_list[i]; i++)
	{
		memcpy(&inAddr, IpHost->h_addr_list[i], 4);
		strcpy_s(szIP, sizeof(szIP), inet_ntoa(inAddr));
		cout << "IP Adress : " << szIP << endl;
	}
	ENABLE_C4996
	return true;
}

int main()
{
	ServerNet* server = ServerNet::GetInstans();
	//Scene * scene = new Scene();
	std::unique_ptr<Login> login = std::make_unique<Login>();
	
	server->CreateSocket();

	// サーバーの受け入れ準備
	if (server->Listen() != 0)
	{
		return 0;
	}

	// ホストIPを獲得＆表示
	for (int i = 0; i < 5; i++)
	{
		if (GetHostIp() == false)
		{
			continue;
		}
		break;
	}


	// クライアントソケットを一時的に獲得する。
	SOCKET m_soc;
	// クライアントアドレスを一時的に獲得する。
	sockaddr_in m_addr;
	// ルームのリスト
	map<int, Room*> roomList;


	while (true)
	{
		// 最初の接続受付
		if (server->Accept(&m_soc, &m_addr) == 0)
		{
			if (m_soc > 0 && 999 > m_soc)
			{
				// 接続されたらLoginさせる
				Player p = login->Execution(m_soc, m_addr);
				// LoginしたPlayerをルームに突っ込む
				if (p.socket != 0)
				{
					// ルームが作られていないなら
					if (roomList.size() == 0)
					{
						// ルームの作成 & プレイヤーの入室
						roomList.insert(make_pair(0, new Room(0, p)));
						cout << "ルーム0を作成" << endl;
						cout << "ルーム0に " << p.socket << " 入室" << endl;
					}
					// 作られているなら
					else
					{
						int num = 0;
						bool tmp = false;
						// ルームリストを回して
						for (map<int, Room*>::iterator itr = roomList.begin(); itr != roomList.end(); itr++)
						{
							// 空きを検索
							if ((itr)->second->GetPlayerNum() < (itr)->second->MAX_ROOM_MEMBER_NUM)
							{
								// 入室許可を出しているか
								if ((itr)->second->GetEntry() == 0)
								{
									// 開いていたら入室
									(itr)->second->PushList(p);
									cout << "ルーム" << (itr)->second->m_roomNum << "に " << p.socket << " が入室" << endl;
									tmp = true;
									break;
								}
							}
							// 全て埋まっていたら
							if (++itr == roomList.end())
							{
								int i = 0;
								for (;;)
								{
									if (roomList.find(i) != roomList.end()) { break; }
									i++;
								}
								// 新しくルームを作って入室
								roomList.insert(make_pair(i, new Room(i, p)));
								cout << "ルーム" << roomList.size() << "を作成" << endl;
								cout << "ルーム" << roomList.size() << "に " << p.socket << " が入室" << endl;
							}
							--itr;
						}
					}
				}
			}
		}
		
		// ルームの数が0でなかったらルームの更新
		if (roomList.size() != 0)
		{
			int roomNum = 0;
			// ルームの更新処理
			for (map<int, Room*>::iterator itr = roomList.begin(); itr != roomList.end(); itr++)
			{
				roomNum++;
				// 受信
				(itr)->second->Receive();
				// 送信
				(itr)->second->Execution();
			}
			// ルームの削除
			for (map<int, Room*>::iterator itr = roomList.begin(); itr != roomList.end(); itr++)
			{
				if ((itr)->second->GetEntry() == 3)
				{
					itr = roomList.erase(itr);
				}
			}
		}
	}
	return 0;
}
