#pragma once
//// �}���`�X���b�h�쐬�ɕK�v
//#include <thread>
//// �����X���b�h�����̏�����G�������ɖ�肪�N���Ȃ��悤�ɂ��邽�߂̂���
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

	// �X���b�h�̌Œ�p
	//std::mutex m_mutex;

	ServerNet* server;
	char m_data[1024];
};

