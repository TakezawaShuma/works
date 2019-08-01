#pragma once
//// マルチスレッド作成に必要
//#include <thread>
//// 複数スレッドから一つの処理を触った時に問題が起きないようにするためのもの
//#include <mutex>

#include "../../Data.h"

class ServerNet;

class Login
{
public:
	Login();
	~Login();

	//static Login* Getinstans();

	Player Execution(SOCKET _soc, sockaddr_in _addr);

private:

	//static Login* m_instans;

	// スレッドの固定用
	//std::mutex m_mutex;

	ServerNet* server;
	char m_data[1024];
};

