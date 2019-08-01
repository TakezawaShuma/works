// プリコンパイル済みヘッダー ---------
#include "pch.h"
// ------------------------------------
// 既存 -------------------------------
#include <WinSock2.h>
// ------------------------------------
#include "NetworkClient.h"

/// <summary>
/// コンストラクタ
/// </summary>
NetworkClient::NetworkClient():m_mySocket(0),m_socket(0)
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
}

/// <summary>
/// デストラクタ
/// </summary>
NetworkClient::~NetworkClient()
{

}


/// <summary>
/// 接続
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

	// ソケット作成
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	// 接続
	if (connect(m_socket, (struct sockaddr *)&destAddr, sizeof(destAddr)) == SOCKET_ERROR) {
		// 失敗
		return false;
	}

	u_long val = 1;
	ioctlsocket(m_socket, FIONBIO, &val);
	return true;
}

/// <summary>
/// 受信
/// </summary>
/// <param name="_data">格納するポインタ</param>
/// <param name="_dateSize">データのサイズ</param>
/// <param name="_recvSize">受信データのサイズ</param>
/// <param name="_obj">コールバッククラス</param>
/// <returns></returns>
RECVSTATUS NetworkClient::Recv(char * _data, int _dateSize, int * _recvSize, IReception* _obj)
{
	RECVSTATUS state = RECVSTATUS::RECV_STILL;
	// 送られてきたデータを全て取得
	while (true)
	{
		int n = recv(m_socket, _data, _dateSize, 0);

		if (n < 1)
		{
			// データなし
			if (WSAGetLastError() == WSAEWOULDBLOCK)	break;
			// 切断
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
/// 受信
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
		// データなし
		if (WSAGetLastError() == WSAEWOULDBLOCK) { return RECVSTATUS::RECV_STILL; }
		// 切断
		else {return RECVSTATUS::RECV_FAILED; }
	}
	else
	{
		*_recvSize = n;
		return RECVSTATUS::RECV_SUCCESSED;
	}
}

/// <summary>
/// 送信
/// </summary>
/// <param name="_data">送るデータのポインタ</param>
/// <param name="_dataSize">送るデータのサイズ</param>
/// <returns></returns>
bool NetworkClient::Send(char * _data, int _dataSize)
{
	// パケット送信
	if (send(m_socket, _data, _dataSize, 0) == SOCKET_ERROR) {
		// 失敗
		return false;
	}
	return true;
}

/// <summary>
/// ソケットのクローズ
/// </summary>
/// <param name="_destSocket">指定ソケット</param>
void NetworkClient::Close(SOCKET _destSocket)
{
	closesocket(_destSocket);
}

// 自身を閉じる
/// <summary>
/// 自身を閉じてソケット内をクリーンアップする
/// </summary>
void NetworkClient::Lost()
{
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
	}
	WSACleanup();
}
