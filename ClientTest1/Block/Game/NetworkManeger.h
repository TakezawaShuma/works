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

	// ログインで必要なものだけ受け取る
	SOCKET Recv();
	// 送られてきたデータ全てを受け取る
	RECVSTATUS Recv(IReception* _obj);


protected:
	NetworkManeger();
	~NetworkManeger();
private:
	bool m_connected;


	// 受信データを保管する
	char m_data[1024];
	// 受信データのサイズを確保する
	int m_dataSize;
};

