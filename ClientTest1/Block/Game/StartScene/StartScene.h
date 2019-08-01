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

		// �J�n����
		void Start();

		// �X�V
		bool Update();

	private:
		System::EffectManager* m_effect;
	};
}