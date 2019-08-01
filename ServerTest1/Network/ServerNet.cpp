#include "../stdafx.h"
#include "ServerNet.h"
#include <stdio.h>
#include <iostream>

#define PORT 10000

ServerNet* ServerNet::m_instans = nullptr;

/// <summary>
/// コンストラクタ
/// WinSock2の初期化
/// </summary>
ServerNet::ServerNet()
{
	WSADATA wsaData;

	// WinSockのバージョン決定＆初期化
	if (WSAStartup(MAKEWORD(2, 0), &wsaData))
	{
		printf("WinSock の初期化に失敗しました");
	}
}

ServerNet::~ServerNet()
{

}

/// <summary>
/// 実体化
/// シングルトン化
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
/// ソケットの作成＆バインド
/// </summary>
/// <returns>成功 = 0 / 失敗 = -1</returns>
int ServerNet::CreateSocket()
{
	// ソケットの作成
	m_soc = socket(AF_INET, SOCK_STREAM, 0);
	if (m_soc == INVALID_SOCKET)
	{
		printf("ソケット作成時にエラー");
		return -1;
	}

	// ソケットの設定
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(PORT); 
	m_addr.sin_addr.s_addr = INADDR_ANY;

	// ソケットのバインド
	if (bind(m_soc, (sockaddr*)&m_addr, sizeof(m_addr)) != 0)
	{
		printf("ソケットのバインドに失敗しました");
		return -1;
	}
	return 0;
}

/// <summary>
/// 接続受け入れ
/// </summary>
/// <returns> 成功 = 0 / 失敗 = -1 </returns>
int ServerNet::Listen()
{
	if (listen(m_soc, 5))
	{
		printf("接続準備に失敗しました");
		return -1;
	}
	u_long val = 1;
	ioctlsocket(m_soc, FIONBIO, &val);

	return 0;
}

/// <summary>
/// 接続判定
/// </summary>
/// <param name="_soc">接続先のソケットを入れて置く</param>
/// <param name="_destAddr">接続するアドレス</param>
/// <returns> 成功 = 0 / 失敗 = -1</returns>
int ServerNet::Accept(SOCKET* _soc, sockaddr_in* _destAddr)
{
	// スレッドをロック
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
/// 受信
/// </summary>
/// <param name="_soc">クライアントソケット</param>
/// <param name="_data">送られてくるデータを入れる</param>
/// <param name="_dataSize">送られてくるデータのサイズ</param>
/// <param name="_recvSize">送られてきたデータのサイズを入れておく</param>
/// <returns></returns>
RECV_CONNECTION ServerNet::Recv(SOCKET _soc, char * _data, int _dataSize, int * _recvSize)
{
	// スレッドをロック
	std::lock_guard<std::mutex> lock(m_mutex);

	RECV_CONNECTION state = RECV_CONNECTION::RECV_NON_DATA;
	int n;
	while (true)
	{	
		n = recv(_soc, _data, _dataSize, 0);

		if (n < 1)
		{
			// データなし
			if (WSAGetLastError() == WSAEWOULDBLOCK)	break;
			// 切断
			else { state = RECV_CONNECTION::RECV_FAILURE;		break; }
		}
		else { state = RECV_CONNECTION::RECV_SUCCESS;	*_recvSize = n;
		}
	}
	return state;
}

/// <summary>
/// 送信
/// </summary>
/// <param name="_soc">送るソケット</param>
/// <param name="_data">送るデータ</param>
/// <param name="_dataSize">送るデータサイズ</param>
/// <returns></returns>
int ServerNet::Send(SOCKET _sendSoc, char * _sendData, int _sendDataSize)
{
	int a = send(_sendSoc, _sendData, _sendDataSize, 0);
	printf("%d\n", _sendSoc);
	if (a == SOCKET_ERROR)
	{
		printf("%d", GetLastError());
		Data::ErrorState(GetLastError());
		printf("送信に失敗しました\n");
		return - 1;
	}

	return 0;
}

/// <summary>
/// 切断
/// </summary>
/// <param name="_destSocket">閉じるソケット</param>
/// <returns></returns>
bool ServerNet::Close(SOCKET _destSocket)
{
	if (closesocket(_destSocket) != 0)
	{
		printf("切断失敗\n");
		return false;
	}
		return true;
}

