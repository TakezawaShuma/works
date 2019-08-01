// ServerTest1.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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
	HOSTENT* IpHost;	// �z�X�g�����i�[���Ă����\����
	IN_ADDR inAddr;		// IP�A�h���X���i�[���Ă����\����
	char szBuf[256], szIP[16];		// �z�X�g�� / IP�A�h���X���i�[���Ă����z��


	DISABLE_C4996		
									// ���[�J���}�V���̃z�X�g�����擾����
	if (gethostname(szBuf, (int)sizeof(szBuf)) != 0)
	{
		// �G���[����
		cout << "�z�X�g�����擾�o���܂���ł����B" << endl;
		// �G���[�i���o�[���擾����
		int err = WSAGetLastError();
		cout << "ERRORNUMBER : " << err << endl;
		Data::ErrorState(err);
		return false;
	}
	cout << "HOST Name : " << szBuf << endl;

	// �z�X�g��񂩂�IP�A�h���X���̏����擾����
	IpHost = gethostbyname(szBuf);
	// �G���[����
	if (IpHost == NULL)
	{
		cout << "IP�A�h���X���擾�ł��܂���ł���" << endl;
		// �G���[�i���o�[���擾����
		int err = WSAGetLastError();
		cout << "ERRORNUMBER : " << err << endl;
		Data::ErrorState(err);
		return false;
	}	
	// IP�A�h���X���擾
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

	// �T�[�o�[�̎󂯓��ꏀ��
	if (server->Listen() != 0)
	{
		return 0;
	}

	// �z�X�gIP���l�����\��
	for (int i = 0; i < 5; i++)
	{
		if (GetHostIp() == false)
		{
			continue;
		}
		break;
	}


	// �N���C�A���g�\�P�b�g���ꎞ�I�Ɋl������B
	SOCKET m_soc;
	// �N���C�A���g�A�h���X���ꎞ�I�Ɋl������B
	sockaddr_in m_addr;
	// ���[���̃��X�g
	map<int, Room*> roomList;


	while (true)
	{
		// �ŏ��̐ڑ���t
		if (server->Accept(&m_soc, &m_addr) == 0)
		{
			if (m_soc > 0 && 999 > m_soc)
			{
				// �ڑ����ꂽ��Login������
				Player p = login->Execution(m_soc, m_addr);
				// Login����Player�����[���ɓ˂�����
				if (p.socket != 0)
				{
					// ���[��������Ă��Ȃ��Ȃ�
					if (roomList.size() == 0)
					{
						// ���[���̍쐬 & �v���C���[�̓���
						roomList.insert(make_pair(0, new Room(0, p)));
						cout << "���[��0���쐬" << endl;
						cout << "���[��0�� " << p.socket << " ����" << endl;
					}
					// ����Ă���Ȃ�
					else
					{
						int num = 0;
						bool tmp = false;
						// ���[�����X�g���񂵂�
						for (map<int, Room*>::iterator itr = roomList.begin(); itr != roomList.end(); itr++)
						{
							// �󂫂�����
							if ((itr)->second->GetPlayerNum() < (itr)->second->MAX_ROOM_MEMBER_NUM)
							{
								// ���������o���Ă��邩
								if ((itr)->second->GetEntry() == 0)
								{
									// �J���Ă��������
									(itr)->second->PushList(p);
									cout << "���[��" << (itr)->second->m_roomNum << "�� " << p.socket << " ������" << endl;
									tmp = true;
									break;
								}
							}
							// �S�Ė��܂��Ă�����
							if (++itr == roomList.end())
							{
								int i = 0;
								for (;;)
								{
									if (roomList.find(i) != roomList.end()) { break; }
									i++;
								}
								// �V�������[��������ē���
								roomList.insert(make_pair(i, new Room(i, p)));
								cout << "���[��" << roomList.size() << "���쐬" << endl;
								cout << "���[��" << roomList.size() << "�� " << p.socket << " ������" << endl;
							}
							--itr;
						}
					}
				}
			}
		}
		
		// ���[���̐���0�łȂ������烋�[���̍X�V
		if (roomList.size() != 0)
		{
			int roomNum = 0;
			// ���[���̍X�V����
			for (map<int, Room*>::iterator itr = roomList.begin(); itr != roomList.end(); itr++)
			{
				roomNum++;
				// ��M
				(itr)->second->Receive();
				// ���M
				(itr)->second->Execution();
			}
			// ���[���̍폜
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
