// �v���R���p�C���ς݃w�b�_�[ ---------
#include "pch.h"
// ------------------------------------
// ���� -------------------------------
#include <WinSock2.h>
// ------------------------------------
#include "NetworkClient.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
NetworkClient::NetworkClient():m_mySocket(0),m_socket(0)
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NetworkClient::~NetworkClient()
{

}


/// <summary>
/// �ڑ�
/// </summary>
/// <param name="_ip"></param>
/// <param name="_port"></param>
/// <returns></returns>
bool NetworkClient::Connect(const char * _ip, u_short _port)
{
	struct sockaddr_in destAddr;
	memset(&destAddr, 0, sizeof(destAddr));
	destAddr.sin_port = htons(_port);
	destAddr.sin_family = AF_INET;
	destAddr.sin_addr.s_addr = inet_addr(_ip);

	// �\�P�b�g�쐬
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	// �ڑ�
	if (connect(m_socket, (struct sockaddr *)&destAddr, sizeof(destAddr)) == SOCKET_ERROR) {
		// ���s
		return false;
	}

	u_long val = 1;
	ioctlsocket(m_socket, FIONBIO, &val);
	return true;
}

/// <summary>
/// ��M
/// </summary>
/// <param name="_data">�i�[����|�C���^</param>
/// <param name="_dateSize">�f�[�^�̃T�C�Y</param>
/// <param name="_recvSize">��M�f�[�^�̃T�C�Y</param>
/// <param name="_obj">�R�[���o�b�N�N���X</param>
/// <returns></returns>
RECVSTATUS NetworkClient::Recv(char * _data, int _dateSize, int * _recvSize, IReception* _obj)
{
	RECVSTATUS state = RECVSTATUS::RECV_STILL;
	// �����Ă����f�[�^��S�Ď擾
	while (true)
	{
		int n = recv(m_socket, _data, _dateSize, 0);

		if (n < 1)
		{
			// �f�[�^�Ȃ�
			if (WSAGetLastError() == WSAEWOULDBLOCK)	break;
			// �ؒf
			else { state = RECVSTATUS::RECV_FAILED;		break; }
		}
		else
		{
			state = RECVSTATUS::RECV_SUCCESSED;
			*_recvSize = n;
			_obj->Reception(_data);
		}
	}
	return state;
}

/// <summary>
/// ��M
/// </summary>
/// <param name="_data"></param>
/// <param name="_dateSize"></param>
/// <param name="_recvSize"></param>
/// <returns></returns>
RECVSTATUS NetworkClient::Recv(char * _data, int _dateSize, int * _recvSize)
{
	int n = recv(m_socket, _data, _dateSize, 0);

	if (n < 1)
	{
		// �f�[�^�Ȃ�
		if (WSAGetLastError() == WSAEWOULDBLOCK) { return RECVSTATUS::RECV_STILL; }
		// �ؒf
		else {return RECVSTATUS::RECV_FAILED; }
	}
	else
	{
		*_recvSize = n;
		return RECVSTATUS::RECV_SUCCESSED;
	}
}

/// <summary>
/// ���M
/// </summary>
/// <param name="_data">����f�[�^�̃|�C���^</param>
/// <param name="_dataSize">����f�[�^�̃T�C�Y</param>
/// <returns></returns>
bool NetworkClient::Send(char * _data, int _dataSize)
{
	// �p�P�b�g���M
	if (send(m_socket, _data, _dataSize, 0) == SOCKET_ERROR) {
		// ���s
		return false;
	}
	return true;
}

/// <summary>
/// �\�P�b�g�̃N���[�Y
/// </summary>
/// <param name="_destSocket">�w��\�P�b�g</param>
void NetworkClient::Close(SOCKET _destSocket)
{
	closesocket(_destSocket);
}

// ���g�����
/// <summary>
/// ���g����ă\�P�b�g�����N���[���A�b�v����
/// </summary>
void NetworkClient::Lost()
{
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
	}
	WSACleanup();
}
