#pragma once

#include "../TaskBase.h"
#include "../Effects/EffectManager.h"

namespace MyGame
{
	class StartScene : public Task::TaskBase
	{
	public:

		StartScene(System::EffectManager* _effect);

		~StartScene();

		// 開始処理
		void Start();

		// 更新
		bool Update();

	private:
		System::EffectManager* m_effect;
	};
}