#include "../../../stdafx.h"
#include "PlayScene.h"

using namespace Utility;

Play::Play():m_marginalTime(0)
{
}

Play::~Play()
{
}

bool Play::HitChack(Vector2 _v1, Vector2 _v2)
{
	// 点__v2と中心_v1半径16とのあたり判定
	if (Collistions::GetInstans()->HitCircleAndPoint(_v2, _v1, 16))
	{
		return true;
	}
	return false;
}

/// <summary>
/// Play の更新(あたり判定＆ダメージ)
/// </summary>
/// <param name="_p1"></param>
/// <param name="_p2"></param>
/// <returns></returns>
bool Play::Execution(Player* _p1, Player* _p2)
{
	bool flag = false;
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// あたり判定
		// p1自身とp2の弾とのあたり判定
		if (_p2->bulletActive[i] == true)
		{
			if (this->HitChack(Vector2(_p1->posX, _p1->posY), Vector2(_p2->bulletPosX[i], _p2->bulletPosY[i])))
			{
  				_p2->bulletActive[i] = false;
				_p1->hitPoint -= 1;
				flag = true;
				std::cout << "弾が当たりました" << std::endl;
			}
		}
	}

	return flag;
}

/// <summary>
/// 
/// </summary>
/// <param name="_p"></param>
/// <returns></returns>
int Play::SceneFlag(Player  _p)
{
	return _p.changeSceneFlag;
}

