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
/// ログイン＆ルーム振り分け
/// </summary>
/// <param name="_soc"></param>
/// <param name="_addr"></param>
/// <returns></returns>
Player Login::Execution(SOCKET _soc, sockaddr_in _addr)
{
	// プレイヤーの初期化＆獲得
	Player p = Player(_soc);
	memcpy(m_data, &_soc, sizeof(SOCKET));
	// 情報を送ってクライアントに自身を獲得させる(SCENE::LOGIN)
	if (server->Send(_soc, m_data, sizeof(m_data)) != 0)
	{
		p = Player();
		return p;
	}

	return p;
}