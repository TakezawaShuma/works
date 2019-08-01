#pragma once
// ���� -------------------------------
#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
// ------------------------------------
// �R�[���o�b�N -----------------------
#include "Callback.h"
// ------------------------------------
// �V���O���g�� -----------------------
#include "Game\Utility\SingletonBase.h"
// ------------------------------------
// ���C�u���� -------------------------
#pragma comment(lib,"ws2_32.lib")
// ------------------------------------
#define PORT 10000

struct PlayerData;

/// <summary>
/// ��M��
/// </summary>
enum RECVSTATUS
{
	// �f�[�^�����Ă��Ȃ�
	RECV_STILL,
	// ����
	RECV_SUCCESSED,
	// �ؒfor�G���[
	RECV_FAILED
};

/// <summary>
/// �N���C�A���g��
/// </summary>
class NetworkClient:public Utility::SingletonBase<NetworkClient>
{
public:

	friend class Utility::SingletonBase<NetworkClient>;

	// �ڑ�
	bool Connect(const char* _ip, u_short _port);
	// �f�[�^�̎�M
	RECVSTATUS Recv(char *_data, int _dateSize, int *_recvSize, IReception* _obj);
	RECVSTATUS Recv(char *_data, int _dateSize, int *_recvSize);

	// �f�[�^�̑��M
	bool Send(char *_data, int _dataSize);
	// �ؒf
	void Close(SOCKET _destSocket);

	void Lost();

	// �\�P�b�g
	SOCKET GetMySocket() { return m_mySocket; }
	void SetMySocket(SOCKET _soc) { m_mySocket = _soc; }

	// IP��ݒ肷��
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

	// �T�[�o�[���̃\�P�b�g
	SOCKET m_socket;

	// ���g�̃\�P�b�g
	SOCKET m_mySocket;

	// �ڑ����IP�A�h���X�̃|�C���^
	std::string m_connectIP;
};

