#pragma once
#include "../NetworkClient.h"
#include "../Data.h"
#include "Utility\SingletonBase.h" 
#include "../Callback.h"

class NetworkManeger :public Utility::SingletonBase<NetworkManeger>
{
public:

	friend class Utility::SingletonBase<NetworkManeger>;

public:

	void Start();
	void Execution();
	void Drow();

	// ���O�C���ŕK�v�Ȃ��̂����󂯎��
	SOCKET Recv();
	// �����Ă����f�[�^�S�Ă��󂯎��
	RECVSTATUS Recv(IReception* _obj);


protected:
	NetworkManeger();
	~NetworkManeger();
private:
	bool m_connected;


	// ��M�f�[�^��ۊǂ���
	char m_data[1024];
	// ��M�f�[�^�̃T�C�Y���m�ۂ���
	int m_dataSize;
};

