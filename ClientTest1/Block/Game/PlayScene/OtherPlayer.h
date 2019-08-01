#pragma once
// 既存 -------------------------------
#include <vector>
//-------------------------------------
// 継承元 -----------------------------
#include "../GameObject.h"
// ------------------------------------
// 弾 ---------------------------------
#include "Bullet.h"
// ------------------------------------
// その他 -----------------------------
#include "../../Data.h"
// ------------------------------------

class OtherPlayer : public GameObject
{
private: // 定数

	static const int PLAYER_SIZE_X = 32;
	static const int PLAYER_SIZE_Y = 32;

public:
	// コンストラクタ
	OtherPlayer(); 
	OtherPlayer(PlayerData _playerData);

	// デストラクタ
	~OtherPlayer();

	// データの更新
	void Recv(float _x, float _y,float _angle);
	void RecvBullet(float _x, float _y, bool _is, int _index);

	// 開始
	void Start();

	// 更新
	void Update();
	void Update(PlayerData _playerData);

	// 描画
	void TextureUpdate(DirectX::SimpleMath::Vector2 _pos);
	void Draw();
	void DrawBegin();
	void DrawEnd();


	// ソケットのゲッター
	SOCKET GetSocket() { return m_socket; }
	Bullet* GetBullet(int _index) { return &m_bullet[_index]; }

private:
	DirectX::SimpleMath::Vector2 MoveDirection(float _direction);

	
private:
	// ソケット
	SOCKET m_socket;

	// HP
	int m_hitPoint;

	// プレイヤーのポジションを保管
	DirectX::SimpleMath::Vector2 m_playerPosition;

	// 他のプレイヤーの弾
	Bullet m_bullet[BULLET_NUM];
	int m_number;

	SCENE m_nowScene;

	bool m_active;
};