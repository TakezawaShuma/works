#pragma once
#ifndef DATA_DEFINED
#define DATA_DEFINED

#include <WinSock2.h>

#define BULLET_NUM 25
class Data {
public:		// 定数や列挙
	// コネクターの状態
	enum SCENE
	{
		//接続時
		LOGIN,
		// タイトルシーン
		TITLE,
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

public:		// 関数
	// ネットワークのエラー状態
	static void ErrorState(int errorNumber);
private:
};

struct Player
{
	/// <summary>
	/// コンストラクタ(何も入れない)
	/// </summary>
	Player() :posX(0), posY(0), angle(0), hitPoint(5), socket(0), scene(Data::SCENE::NON), nextScene(Data::SCENE::NON), changeSceneFlag(0)
	{
		for (int a = 0; a < BULLET_NUM; a++)
		{
			bulletPosX[a] = 0;
			bulletPosY[a] = 0;
			bulletActive[a] = false;
		}
	}
	/// <summary>
	/// コンストラクタ(ソケットを獲得):posX(0), posY(0), angle(0), hitPoint(5), socket(_soc), scene(SCENE::LOBBY), nextScene(SCENE::NON), changeSceneFlag(0)
	/// </summary>
	/// <param name="_soc"></param>
	Player(SOCKET _soc) :posX(0), posY(0), angle(0), hitPoint(5), socket(_soc), scene(Data::SCENE::LOBBY), nextScene(Data::SCENE::NON), changeSceneFlag(0)
	{
		for (int a = 0; a < BULLET_NUM; a++)
		{
			bulletPosX[a] = 0;
			bulletPosY[a] = 0;
			bulletActive[a] = false;
		}
	}

	// コネクターのソケット
	SOCKET socket;

	// コネクターの体力
	int hitPoint;

	// コネクターの位置
	float posX;
	float posY;

	// 向いている角度
	float angle;

	// 弾の数＆位置＆有無効
	float bulletPosX[BULLET_NUM];
	float bulletPosY[BULLET_NUM];
	bool bulletActive[BULLET_NUM];


	int rank;

	// プレイヤーの現在のシーン(クライアントで切り替える)
	Data::SCENE scene;
	// プレイヤーの次切り替えるシーン(サーバーで切り替える)
	Data::SCENE nextScene;
	// シーンの切り替え許可(1 = 次のシーンへ・0 = 待機・-1 = 前のシーンへ)
	int changeSceneFlag;
};

#endif // !DATA_DEFINED