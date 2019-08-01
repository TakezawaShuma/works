#pragma once
//// マルチスレッド作成に必要
//#include <thread>
//// 複数スレッドから一つの処理を触った時に問題が起きないようにするためのもの
//#include <mutex>

#include "../../Data.h"
#include <list>

class Lobby
{
public:
	Lobby();
	~Lobby();

	//// インスタンスの獲得
	//static Lobby* GetInstans();

	// 実行
	//SCENE Execution(Player _p1);
	int SceneFlag(Player _p1);
	

	std::list<Player> Execution();

private:
	//// インスタンス
	//static Lobby* m_instans;

	//// スレッド固定用
	//std::mutex m_mutex;
};

