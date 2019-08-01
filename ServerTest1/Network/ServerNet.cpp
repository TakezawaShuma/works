#include "../stdafx.h"
#include "ServerNet.h"
#include <stdio.h>
#include <iostream>

#define PORT 10000

ServerNet* ServerNet::m_instans = nullptr;

/// <summary>
/// �R���X�g���N�^
/// WinSock2�̏�����
/// </summary>
ServerNet::ServerNet()
{
	WSADATA wsaData;

	// WinSock�̃o�[�W�������聕������
	if (WSAStartup(MAKEWORD(2, 0), &wsaData))
	{
		printf("WinSock �̏������Ɏ��s���܂���");
	}
}

ServerNet::~ServerNet()
{

}

/// <summary>
/// ���̉�
/// �V���O���g����
/// </summary>
/// <returns></returns>
ServerNet * ServerNet::GetInstans()
{
	if (m_instans == nullptr)
	{
		m_instans = new ServerNet();
	}
	return m_instans;
}

/// <summary>
/// �\�P�b�g�̍쐬���o�C���h
/// </summary>
/// <returns>���� = 0 / ���s = -1</returns>
int ServerNet::CreateSocket()
{
	// �\�P�b�g�̍쐬
	m_soc = socket(AF_INET, SOCK_STREAM, 0);
	if (m_soc == INVALID_SOCKET)
	{
		printf("�\�P�b�g�쐬���ɃG���[");
		return -1;
	}

	// �\�P�b�g�̐ݒ�
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(PORT); 
	m_addr.sin_addr.s_addr = INADDR_ANY;

	// �\�P�b�g�̃o�C���h
	if (bind(m_soc, (sockaddr*)&m_addr, sizeof(m_addr)) != 0)
	{
		printf("�\�P�b�g�̃o�C���h�Ɏ��s���܂���");
		return -1;
	}
	return 0;
}

/// <summary>
/// �ڑ��󂯓���
/// </summary>
/// <returns> ���� = 0 / ���s = -1 </returns>
int ServerNet::Listen()
{
	if (listen(m_soc, 5))
	{
		printf("�ڑ������Ɏ��s���܂���");
		return -1;
	}
	u_long val = 1;
	ioctlsocket(m_soc, FIONBIO, &val);

	return 0;
}

/// <summary>
/// �ڑ�����
/// </summary>
/// <param name="_soc">�ڑ���̃\�P�b�g�����Ēu��</param>
/// <param name="_destAddr">�ڑ�����A�h���X</param>
/// <returns> ���� = 0 / ���s = -1</returns>
int ServerNet::Accept(SOCKET* _soc, sockaddr_in* _destAddr)
{
	// �X���b�h�����b�N
	std::lock_guard<std::mutex> lock(m_mutex);

	int clientAddrSize = sizeof(sockaddr_in);

	*_soc = accept(m_soc, (sockaddr*)_destAddr, &clientAddrSize);
	if (*_soc != INVALID_SOCKET)
	{
		u_long val = 1;
		ioctlsocket(*_soc, FIONBIO, &val);
		return 0;
	}
	return -1;
}

/// <summary>
/// ��M
/// </summary>
/// <param name="_soc">�N���C�A���g�\�P�b�g</param>
/// <param name="_data">�����Ă���f�[�^������</param>
/// <param name="_dataSize">�����Ă���f�[�^�̃T�C�Y</param>
/// <param name="_recvSize">�����Ă����f�[�^�̃T�C�Y�����Ă���</param>
/// <returns></returns>
RECV_CONNECTION ServerNet::Recv(SOCKET _soc, char * _data, int _dataSize, int * _recvSize)
{
	// �X���b�h�����b�N
	std::lock_guard<std::mutex> lock(m_mutex);

	RECV_CONNECTION state = RECV_CONNECTION::RECV_NON_DATA;
	int n;
	while (true)
	{	
		n = recv(_soc, _data, _dataSize, 0);

		if (n < 1)
		{
			// �f�[�^�Ȃ�
			if (WSAGetLastError() == WSAEWOULDBLOCK)	break;
			// �ؒf
			else { state = RECV_CONNECTION::RECV_FAILURE;		break; }
		}
		else { state = RECV_CONNECTION::RECV_SUCCESS;	*_recvSize = n;
		}
	}
	return state;
}

/// <summary>
/// ���M
/// </summary>
/// <param name="_soc">����\�P�b�g</param>
/// <param name="_data">����f�[�^</param>
/// <param name="_dataSize">����f�[�^�T�C�Y</param>
/// <returns></returns>
int ServerNet::Send(SOCKET _sendSoc, char * _sendData, int _sendDataSize)
{
	int a = send(_sendSoc, _sendData, _sendDataSize, 0);
	printf("%d\n", _sendSoc);
	if (a == SOCKET_ERROR)
	{
		printf("%d", GetLastError());
		Data::ErrorState(GetLastError());
		printf("���M�Ɏ��s���܂���\n");
		return - 1;
	}

	return 0;
}

/// <summary>
/// �ؒf
/// </summary>
/// <param name="_destSocket">����\�P�b�g</param>
/// <returns></returns>
bool ServerNet::Close(SOCKET _destSocket)
{
	if (closesocket(_destSocket) != 0)
	{
		printf("�ؒf���s\n");
		return false;
	}
		return true;
}

