#pragma once
//// �}���`�X���b�h�쐬�ɕK�v
//#include <thread>
//// �����X���b�h�����̏�����G�������ɖ�肪�N���Ȃ��悤�ɂ��邽�߂̂���
//#include <mutex>

#include "../../Data.h"
#include <list>

class Lobby
{
public:
	Lobby();
	~Lobby();

	//// �C���X�^���X�̊l��
	//static Lobby* GetInstans();

	// ���s
	//SCENE Execution(Player _p1);
	int SceneFlag(Player _p1);
	

	std::list<Player> Execution();

private:
	//// �C���X�^���X
	//static Lobby* m_instans;

	//// �X���b�h�Œ�p
	//std::mutex m_mutex;
};

