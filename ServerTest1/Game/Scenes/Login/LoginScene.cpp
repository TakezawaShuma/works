#include "../../../stdafx.h"
#include "LoginScene.h"
#include "../../../Network/ServerNet.h"



Login::Login():server(nullptr)
{
	server = new ServerNet();
}

Login::~Login()
{
	delete server;
}

/// <summary>
/// ���O�C�������[���U�蕪��
/// </summary>
/// <param name="_soc"></param>
/// <param name="_addr"></param>
/// <returns></returns>
Player Login::Execution(SOCKET _soc, sockaddr_in _addr)
{
	// �v���C���[�̏��������l��
	Player p = Player(_soc);
	memcpy(m_data, &_soc, sizeof(SOCKET));
	// ���𑗂��ăN���C�A���g�Ɏ��g���l��������(SCENE::LOGIN)
	if (server->Send(_soc, m_data, sizeof(m_data)) != 0)
	{
		p = Player();
		return p;
	}

	return p;
}