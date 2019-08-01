#pragma once

#include "TaskManager.h"

namespace Task
{
	class TaskBase
	{
	public:	// ��{����

		TaskBase();

		virtual ~TaskBase();

		// �J�n����
		virtual void Start() = 0;

		// �X�V
		virtual bool Update() = 0;

		virtual bool LastUpdate() { return true; };

		// �`��
		virtual void Draw() {};
		virtual void DrawBegin() {};
		virtual void DrawEnd() {};

		// �^�X�N�n���h���̐ݒ�
		void SetThisTaskHandle(TaskHandle hTask)
		{
			mhThisTask = hTask;
		}

		// �^�X�N�n���h���̎擾
		TaskHandle GetThisTaskHandle()
		{
			return mhThisTask;
		}

	private:

		// �^�X�N�n���h��
		TaskHandle mhThisTask;

	private:

	};
}