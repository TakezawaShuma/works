#pragma once
#include <WinSock2.h>
#include <vector>

#define MAX_DATA   5000
#define BULLET_NUM 25

enum SCENE
{
	// タイトルシーン
	TITLE,
	//接続時
	LOGIN,
	// ロビーシーン
	LOBBY,
	// プレイシーン
	PLAY,
	// リザルトシーン
	RESULT,
	// ログアウト＆切断
	LOGOUT,

	// シーンゼロ
	NON,
};


// 通信するプレイヤー情報をまとめた構造体
struct PlayerData
{
	/// <summary>
	/// コンストラクタ(何も入れない)
	/// </summary>
	PlayerData() :posX(0), posY(0), angle(0), hitPoint(5), socket(0), scene(SCENE::NON), nextScene(SCENE::NON), changeSceneFlag(0)
	{
		for (int a = 0; a < BULLET_NUM; a++)
		{
			bulletPosX[a] = 0;
			bulletPosY[a] = 0;
			bulletActive[a] = false;
		}
	}
	/// <summary>
	/// コンストラクタ(ソケットを獲得):posX(0), posY(0), angle(0), hitPoint(5), socket(_soc), scene(SCENE::LOGIN), nextScene(SCENE::LOBBY), changeSceneFlag(true)
	/// </summary>
	/// <param name="_soc"></param>
	PlayerData(SOCKET _soc) :posX(0), posY(0), angle(0), hitPoint(5), socket(_soc), scene(SCENE::LOGIN), nextScene(SCENE::LOBBY), changeSceneFlag(0)
	{
		for (int a = 0; a < BULLET_NUM; a++)
		{
			bulletPosX[a] = 0;
			bulletPosY[a] = 0;
			bulletActive[a] = false;
		}
	}


	SOCKET socket;	// コネクターのソケット
	int hitPoint;	// コネクターの体力
	float posX;		// コネクターのX位置
	float posY;		// コネクターのY位置
	float angle;	// 向いている角度

	float bulletPosX[BULLET_NUM];		// 弾のX位置
	float bulletPosY[BULLET_NUM];		// 弾のY位置
	bool bulletActive[BULLET_NUM];		// 有無効
	
	int rank;		// 順位

	SCENE scene;			// プレイヤーの現在のシーン(クライアントで切り替える)
	SCENE nextScene;		// プレイヤーの次切り替えるシーン(サーバーで切り替える)
	// シーンの切り替え許可
	// 
	int changeSceneFlag;
};
