#pragma once
#include "PlayScene.h"
#include "../GameObject.h"
#include "../../Data.h"
#include "Bullet.h"
#include <vector>

#include <WinSock2.h>



class Player :public GameObject
{
private:
	static const int PLAYER_POSITION_X = 400;
	static const int PLAYER_POSITION_Y = 400;
	static const int MOVE_SPEED = 5;
	static const int MOVE_RANGE = 10;
	static const int PLAYER_SIZE_X = 32;
	static const int PLAYER_SIZE_Y = 32;

public:
	Player();
	Player(SOCKET _soc, DirectX::SimpleMath::Vector2 _pos, int _hp, SCENE _scene);
	~Player();

	
	void Start();	// 初期化処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	void UpdataBullet(bool _active,int _index);		// 弾の更新処理

	// プレイヤーの移動 //
	void MoveUP();
	void MoveDown();
	void RotateRight();
	void RotateLeft();
	//-------------------//

	// ゲッターセッター群
	// GameObject からのもの
	DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }	// ポジションを獲得
	float GetAngle() { return m_angle; }								// アングルを獲得


	// Player 自身のもの
	float GetRadius() { return PLAYER_SIZE_X / 2; }						// 半径を取得
	Bullet* GetBullets(int _index) { return &m_bullet[_index]; }		// 自身の弾の情報を取得
	DirectX::SimpleMath::Vector2 GetDirection() { return m_direction; }	// 向いている方向を取得


	void HP(int _hp) { m_hitPoint = _hp; }								// HP のセット
	int HP() { return m_hitPoint; }										// HP のゲット

	void Damage() { m_hitPoint--; }

	PlayerData GetSend() { return m_sendData; }							// 送る情報の獲得
	void RecvData(PlayerData _playerData);								// 送る情報をセット


	// プレイヤーの現在の状態を sendData に
	void SetSend();

	void UpdateData(PlayerData _data);

	//DirectX::SimpleMath::Vector2 GetTrianglePoint(int _num);



private:		// 関数

	// DirectionをPositionに足す
	DirectX::SimpleMath::Vector2 MoveDirection(float _direction);

private:		// 変数
	SOCKET m_soc;					// プレイヤーのソケット
	u_int m_hitPoint;				// HP
	SCENE m_nowScene;				// 現在のシーン
	SCENE m_nextScene;				// 次のシーン
	Bullet m_bullet[BULLET_NUM];	// プレイヤーの弾
	int m_changeSceneFlag;			// シーンの切り替えフラグ


	// 送るプレイヤーデータ
	PlayerData m_sendData;
	char data[1024];
};
