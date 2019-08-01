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
/// ��M
/// </summary>
void Room::Receive()
{
	// �l�̏���
	for (list<Player>::iterator it = m_playerList.begin(); it != m_playerList.end(); it++)
	{
		int recvSize = 0;
		

		//	�ʐM
		RECV_CONNECTION state = ServerNet::GetInstans()->Recv((it)->socket, m_data, sizeof(m_data), &recvSize);
		
		// �ʐM������������
		if (state == RECV_CONNECTION::RECV_SUCCESS)
		{
			// ����ꂽ�f�[�^��߂�
			Player p;
			memcpy(&p, m_data, sizeof(Player));

			// ���[�����X�g�̃v���C���[�̍X�V
			(*it) = p;

			// �V�[����Play�̎�
			if (it->scene == Data::SCENE::PLAY)
			{
				// �ڑ����؂ꂽ���m�F
				for (list<Player>::iterator ver = m_playerList.begin(); ver != m_playerList.end(); ver++)
				{
					// ������؂ꂽ��
					if (m_play->SceneFlag(*ver) == -1)
					{
						// �f���[�g���X�g�ɒǉ�
 						m_delList.push_back(*ver);
						// �ڑ����؂ꂽ���Ƃ��
						m_sendList.push_back(*ver);
 						continue;
					}
				}
				// ���[���ɐl�����Ȃ��Ȃ�����
				if (m_playerList.size() == 0)
				{
					cout << "���[��" << m_roomNum << " ����ɂȂ�܂����B���[�����폜���܂�" << endl;
					cout << "���[��" << m_roomNum << " ���폜���܂�" << endl;
					// �������폜����
					m_entry = ENTRYSTATE::DELETE_ROOM;
				}
			}
			// �V�[����Lobby�̎��@
			else if (it->scene == Data::SCENE::LOBBY)
			{
				if (it->nextScene != Data::SCENE::NON) { it->nextScene = Data::SCENE::NON; }

				// �����r�[�ɂ���l�𑗂�
				for each(Player tmp in m_playerList) { m_sendList.push_back(tmp); }
				
				// �S�������ɏ�������Ƃ�
				// �S����OK�m�F���Ƃꂽ�Ȃ�V�[���ύX(chack  :: -1 / �ؒf�@, 0 / �������Ȃ��@, 1 / ���̃V�[���� )
				int chack = 0;
				for (list<Player>::iterator ver = m_playerList.begin(); ver != m_playerList.end(); ver++)
				{
					chack = m_lobby->SceneFlag((*ver));
					// �߂��I��������
					if (chack == -1)
					{
						// �f���[�g���X�g�ɒǉ�
						m_delList.push_back(*ver);
						continue;
					}
					else if (chack == 0) { break; }
				}
				// �Q�[���J�n
				if (chack == 1)
				{
					// ���郊�X�g�����
					m_sendList.clear();

					// �v���C�V�[���Ɉڍs���Ă������ƑS���ɋ����o��
					if (m_playerList.size() > 1)
					{
						for (list<Player>::iterator tmp = m_playerList.begin(); tmp != m_playerList.end(); tmp++)
						{
							tmp->nextScene = Data::SCENE::PLAY;
							m_sendList.push_back(*tmp);
						}
					}

					// ��������
					m_entry = ENTRYSTATE::ENTRY_PERMIT;

					cout << "���[��" << m_roomNum << " ��PlayScene�ɂȂ�܂����B" << endl;
					cout << "���[��" << m_roomNum << " �̓����𐧌����܂�" << endl;

				}

				// ���[���ɒN�����Ȃ��Ȃ�����
				if (m_playerList.size() == 0)
				{
					cout << "���[��" << m_roomNum << " ����ɂȂ�܂����B���[�����폜���܂�" << endl;
					cout << "���[��" << m_roomNum << " ���폜���܂�" << endl;
					m_entry = ENTRYSTATE::DELETE_ROOM;
				}
			}
			// �V�[����Result�̎�
			else if (it->scene == Data::SCENE::RESULT)
			{
				// �ڑ����؂ꂽ���m�F
				for (list<Player>::iterator ver = m_playerList.begin(); ver != m_playerList.end(); ver++)
				{
					// ������؂ꂽ��
					if (m_play->SceneFlag(*ver) == -1)
					{
						// �f���[�g���X�g�ɒǉ�
						m_delList.push_back(*ver);
						// �ڑ����؂ꂽ���Ƃ��
						m_sendList.push_back(*ver);
						continue;
					}
				}
				// ���[���ɐl�����Ȃ��Ȃ�����
				if (m_playerList.size() == 0)
				{
					cout << "���[��" << m_roomNum << " ����ɂȂ�܂����B���[�����폜���܂�" << endl;
					cout << "���[��" << m_roomNum << " ���폜���܂�" << endl;
					// �������폜����
					m_entry = ENTRYSTATE::DELETE_ROOM;
				}
			}
		}
		// �ڑ����؂ꂽ�l���폜���X�g�ɓo�^
		else if (state == RECV_CONNECTION::RECV_FAILURE)
		{
			cout << "���[��" << m_roomNum << "���� " << it->socket << " ���ޏo���܂���" << endl;
			it->scene = Data::SCENE::LOGOUT;
			m_sendList.push_back(*it);
			m_delList.push_back(*it);
		}
	}
}

void Room::Execution()
{
	// ���[������̍폜����
	if (m_delList.size() != 0)
	{
		for each (Player var in m_delList)
		{
			for (list<Player>::iterator itr = m_playerList.begin(); itr != m_playerList.end();)
			{
				if (var.socket == itr->socket)
				{
					cout << itr->socket << " ���ؒf���܂���" << endl;
					itr = m_playerList.erase(itr);
					break;
				}
				itr++;
			}
		}
		// ���[�����ɐl�����Ȃ��Ȃ�����
		if (m_entry == ENTRYSTATE::NO_ENTRY && m_playerList.size() < 1)
		{
			cout << "���[��" << m_roomNum << " �͓����\�ł��B" << endl;
			m_entry = ENTRYSTATE::ENTRY_PERMIT;
		}
		m_delList.clear();
	}

	// �����蔻��Ȃǂ��v�Z
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

	// �Z���h���X�g�ɓ����Ă�����
	if (m_sendList.size() != 0)
	{
		// �Z���h���X�g�̒��g�����[���̒��ɂ���l�S���ɑ���
		for each (Player var in m_sendList)
		{
			
			memcpy(m_data, &var, sizeof(Player));
			
			for (list<Player>::iterator it = m_playerList.begin(); it != m_playerList.end(); ++it)
			{

				ServerNet::GetInstans()->Send((*it).socket, m_data, sizeof(m_data));
			}
		}
		// ��������Z���h���X�g������
		m_sendList.clear();
	}
}

void Room::PushList(Player _p)
{
	m_playerList.push_back(_p);
}


