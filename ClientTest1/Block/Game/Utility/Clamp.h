#pragma once
#include "../GameObject.h"
namespace Utility
{
	static bool Clamp(GameObject* object)
	{
		DirectX::SimpleMath::Vector2 pos = object->GetPosition();

		if (pos.x < 0)return true;
		else if (pos.x > 600)return true;
		if (pos.y > 800)return true;
		else if (pos.y < -50)return true;

		return false;
	}
}