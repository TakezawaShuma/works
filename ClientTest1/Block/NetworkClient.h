#pragma once
// 既存 -------------------------------
#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
// ------------------------------------
// コールバック -----------------------
#include "Callback.h"
// ------------------------------------
// シングルトン -----------------------
#include "Game\Utility\SingletonBase.h"
// ------------------------------------
// ライブラリ -------------------------
#pragma comment(lib,"ws2_32.lib")
// ------------------------------------
#define PORT 10000

struct PlayerData;

/// <summary>
/// 受信状況
/// </summary>
enum RECVSTATUS
{
	// データが来ていない
	RECV_STILL,
	// 成功
	RECV_SUCCESSED,
	// 切断orエラー
	RECV_FAILED
};

/// <summary>
/// クライアント側
/// </summary>
class NetworkClient:public Utility::SingletonBase<NetworkClient>
{
public:

	friend class Utility::SingletonBase<NetworkClient>;

	// 接続
	bool Connect(const char* _ip, u_short _port);
	// データの受信
	RECVSTATUS Recv(char *_data, int _dateSize, int *_recvSize, IReception* _obj);
	RECVSTATUS Recv(char *_data, int _dateSize, int *_recvSize);

	// データの送信
	bool Send(char *_data, int _dataSize);
	// 切断
	void Close(SOCKET _destSocket);

	void Lost();

	// ソケット
	SOCKET GetMySocket() { return m_mySocket; }
	void SetMySocket(SOCKET _soc) { m_mySocket = _soc; }

	// IPを設定する
	void IP(std::string _ip) {
		m_connectIP = _ip;
	}
	const char* IP() { return m_connectIP.c_str(); }
	void SetOthrts(SOCKET _soc) { m_otherSoc.push_back(_soc); }
	bool FindOthers(SOCKET _soc) {
		if (std::find(m_otherSoc.begin(), m_otherSoc.end(), _soc) != m_otherSoc.end())
		{
			return true;
		}
		
		return false;
	}

private:

	NetworkClient();
	~NetworkClient();

	std::list<SOCKET> m_otherSoc;

	// サーバー側のソケット
	SOCKET m_socket;

	// 自身のソケット
	SOCKET m_mySocket;

	// 接続先のIPアドレスのポインタ
	std::string m_connectIP;
};

