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
		ENTRY_PERMIT,	// ��������
		NO_ENTRY,		// �����֎~
		DELETE_ROOM,	// ���[���폜
	};

public:
	Room(const int _roomNum);
	Room(const int _roomNum,Player _player);
	~Room();

	// ���̎󂯎��
	void Receive();

	// ���[���̍X�V
	void Execution();
	// ���[���̃��X�g�ɒǉ�
	void PushList(Player _p);

	int GetPlayerNum() { return m_playerList.size(); }
	int GetEntry() { return m_entry; }
private:
	// ���r�[�V�[���̃|�C���^
	std::unique_ptr<Lobby> m_lobby;
	// �v���C�V�[���̃|�C���^
	std::unique_ptr<Play> m_play;

	// ���[���ɓ����Ă���v���C���[
	std::list<Player> m_playerList;

	// ����v���C���[���
	std::list<Player> m_sendList;
	// �폜����v���C���[�̏��
	std::list<Player> m_delList;

	char m_data[1024];

	// �����̉s��
	// 0 = �\�E1 = �s�\�E 3 = ���[���폜 
	ENTRYSTATE m_entry;
};

