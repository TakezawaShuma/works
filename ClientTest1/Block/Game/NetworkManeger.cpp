#include "../pch.h"
#include "NetworkManeger.h"



using namespace std;

NetworkManeger::NetworkManeger()
{
	m_connected = false;

}

NetworkManeger::~NetworkManeger()
{
}


void NetworkManeger::Start()
{

}

void NetworkManeger::Execution()
{

}

void NetworkManeger::Drow()
{

}


RECVSTATUS NetworkManeger::Recv(IReception* _obj)
{
	m_dataSize = 0;
	// éÛêM
	RECVSTATUS state = NetworkClient::GetInstance().Recv(m_data, sizeof(m_data), &m_dataSize, _obj);
	return state;
}


SOCKET NetworkManeger::Recv()
{
	m_dataSize = 0;
	RECVSTATUS state = NetworkClient::GetInstance().Recv(m_data, sizeof(m_data), &m_dataSize);

	SOCKET soc = 0;
	if (state == RECVSTATUS::RECV_SUCCESSED)
	{
		memcpy(&soc, m_data, sizeof(SOCKET));
	}

	return soc;
}



