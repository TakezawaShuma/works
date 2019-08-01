#include "../pch.h"
#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

GameObject::GameObject() :m_position(0, 0), m_angle(0)
{

}

GameObject::GameObject(float _x, float _y) : m_position(_x, _y), m_angle(0),m_direction(Vector2::Zero)
{

}

GameObject::GameObject(Vector2 _pos) : m_position(_pos), m_angle(0), m_direction(Vector2::Zero)
{

}
