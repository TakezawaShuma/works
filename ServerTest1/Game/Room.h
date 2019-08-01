#pragma once
#include<memory>
#include <list>
#include <map>

#include "Data.h"
#include "Scenes/Lobby/LobbyScene.h"
#include "Scenes/Play/PlayScene.h"

#include "../Network/ServerNet.h"


class Room
{
public:
	static const int MAX_ROOM_MEMBER_NUM = 10;
	const int m_roomNum;

	enum ENTRYSTATE
	{
		ENTRY_PERMIT,	// 入室許可
		NO_ENTRY,		// 入室禁止
		DELETE_ROOM,	// ルーム削除
	};

public:
	Room(const int _roomNum);
	Room(const int _roomNum,Player _player);
	~Room();

	// 情報の受け取り
	void Receive();

	// ルームの更新
	void Execution();
	// ルームのリストに追加
	void PushList(Player _p);

	int GetPlayerNum() { return m_playerList.size(); }
	int GetEntry() { return m_entry; }
private:
	// ロビーシーンのポインタ
	std::unique_ptr<Lobby> m_lobby;
	// プレイシーンのポインタ
	std::unique_ptr<Play> m_play;

	// ルームに入っているプレイヤー
	std::list<Player> m_playerList;

	// 送るプレイヤー情報
	std::list<Player> m_sendList;
	// 削除するプレイヤーの情報
	std::list<Player> m_delList;

	char m_data[1024];

	// 入室の可不可
	// 0 = 可能・1 = 不可能・ 3 = ルーム削除 
	ENTRYSTATE m_entry;
};

