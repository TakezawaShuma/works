#pragma once
#include "DrawManager.h"

#define DEBUG true

class GameObject
{
public:
	GameObject();
	GameObject(float _x, float _y);
	GameObject(DirectX::SimpleMath::Vector2 _pos);

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ゲット＆セット
	virtual DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }
	virtual void SetPosition(float _x, float _y) { m_position.x = _x; m_position.y = _y; }
	virtual void SetPosition(DirectX::SimpleMath::Vector2 _pos) { m_position = _pos; }
	virtual float GetAngle() { return m_angle; }
	virtual void SetAngle(float _angle) { m_angle = _angle; }

public:
	const DirectX::SimpleMath::Vector2 POS_ORIGIN = DirectX::SimpleMath::Vector2(400.0f, 400.0f);

protected:
	System::DrawData m_data;						// 画像データ
	DirectX::SimpleMath::Vector2 m_position;		// オブジェクトポジション
	DirectX::SimpleMath::Vector2 m_direction;		// オブジェクトの向き
	float m_angle;									// オブジェクトアングル 
};
