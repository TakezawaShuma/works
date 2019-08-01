#include "../../pch.h"
#include "Bullet.h"

using namespace System;
using namespace DirectX;
using namespace DirectX::SimpleMath; 

// 定数
#define RECT_SIZE 8
#define BULLET_SPEED 5

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet():m_active (false)
{
}

/// <summary>
///	デストラクタ
/// </summary>
Bullet::~Bullet()
{
}

/// <summary>
/// 初期化
/// </summary>
void Bullet::Start()
{
	// 画像の読み込み
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources/PlayScene/Bullet.png");
	m_active = false;
	m_data.SetRect(RECT_SIZE, RECT_SIZE);
	m_data.SetOrigin(RECT_SIZE*0.5, RECT_SIZE*0.5);
}

/// <summary>
/// 弾の発射
/// </summary>
/// <param name="_pos"></param>
/// <param name="_dir"></param>
void Bullet::Shoot(Vector2 _pos, Vector2 _dir)
{
	m_active = true;
	m_data.SetPos(_pos.x, _pos.y);
	m_startPosition = m_position = _pos;
	m_direction = _dir;
}

/// <summary>
/// 更新
/// </summary>
void Bullet::Update()
{
	if (m_active)
	{
		m_position += m_direction*BULLET_SPEED;
		Vector2 s = m_startPosition - m_position;
		m_data.SetPos(POS_ORIGIN - s);
		if (s.Length() > 500) { m_active = false; }
	}
}

/// <summary>
/// 他のプレイヤーの弾の更新
/// </summary>
/// <param name="_pos">自機の位置</param>
void Bullet::OtherUpdate(Vector2 _pos)
{
	if (m_active)
	{
		Vector2 dataPos = _pos - m_position;

		if (dataPos.Length() > 500)
		{
			m_active = false;
		}
		else
		{
			m_data.SetPos(POS_ORIGIN - dataPos);
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void Bullet::Draw()
{
	if (m_active) { DrawManager::GetInstance().Draw(m_data); }
}

void Bullet::DrawBegin()
{
}

void Bullet::DrawEnd()
{
}
