#pragma once
#include "../Game/Data.h"
// �}���`�X���b�h�쐬�ɕK�v
#include <thread>
// �����X���b�h�����̏�����G�������ɖ�肪�N���Ȃ��悤�ɂ��邽�߂̂���
#include <mutex>



#pragma comment (lib,"ws2_32.lib")


// ��M���
enum RECV_CONNECTION
{
	// �ڑ�����
	RECV_SUCCESS,
	// �ڑ����s/�G���[
	RECV_FAILURE,
	// �f�[�^�����Ă��Ȃ�
	RECV_NON_DATA
};

class ServerNet
{
public:
	ServerNet();
	~ServerNet();

	static ServerNet* GetInstans();
	int CreateSocket();
	// �ڑ��p��
	int Listen();
	// �ڑ��m�F
	int Accept(SOCKET* _soc, sockaddr_in* _destAddr);
	// ��M
	RECV_CONNECTION Recv(SOCKET _soc, char* _data, int _dataSize, int* _recvSize);
	// ���M
	int Send(SOCKET _soc, char*_data, int _dataSize);
	// �ؒf
	bool Close(SOCKET _destSocket);
private:
	// �r������p�̕ϐ�
	std::mutex m_mutex;


	static ServerNet* m_instans;

	SOCKET m_soc;
	sockaddr_in m_addr;

};


