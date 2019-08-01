#include "../../pch.h"
#include "MyEffect.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void MyEffect::Create()
{
}

void MyEffect::Initialize(float _life, DirectX::SimpleMath::Vector3 _pos, DirectX::SimpleMath::Vector3 _velocity)
{
	m_startPosition = m_position = _pos;
	m_startVelocity = m_velocity = _velocity;
	m_startLife = m_life = _life;
	m_gravity = Vector3(0, 0.001f, 0);
}

void MyEffect::Update(float _timer)
{
	m_timer = _timer;
}
