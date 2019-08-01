#pragma once
#include "../GameObject.h"

class Bullet : GameObject
{
public:
	Bullet();
	~Bullet();

	// 開始
	void Start();
	
	
	// 発射
	void Shoot(DirectX::SimpleMath::Vector2 _pos,DirectX::SimpleMath::Vector2 _dir);

	// 更新
	void Update();
	void OtherUpdate(DirectX::SimpleMath::Vector2 _pos);

	// 描画
	void Draw();
	void DrawBegin();
	void DrawEnd();

	// ゲッターセッター
	DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }
	void SetPosition(float _x, float _y) { m_position.x = _x; m_position.y = _y; }
	void SetPosition(DirectX::SimpleMath::Vector2 _pos) { m_position = _pos; }

	bool GetActive() { return m_active; }
	void SetActive(bool _is) { m_active = _is; }
public:

private:
	// 生存
	bool m_active;
	// スタートポジション
	DirectX::SimpleMath::Vector2 m_startPosition;
};
