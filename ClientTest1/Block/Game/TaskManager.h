#pragma once

#include <list>

#include "Utility\Flag.h"

namespace Task
{
	class TaskBase;
	class TaskNode;
	class TaskNodeHandle;

	typedef TaskNode* TaskHandle;

	// �^�X�N�}�l�[�W���[�̃t���O�ꗗ
	enum eTaskManagerFlag
	{
		IsDeleted = (1<<0),	// �Ǘ��^�X�N�̍폜���s��ꂽ���̃t���O
	};

	class TaskManager
	{
	public:

		TaskManager();

		~TaskManager();

		// �X�V
		void Update();

		// �`��
		void Draw();

		// �s�v�^�X�N�̍폜
		void CleanTask(bool isWorkTaskDelete = false);

		// �\�񂳂ꂽ�^�X�N��ǉ�����
		void AddReserve();

	public:	// �^�X�N�Ǘ��֐�

		// �^�X�N�ǉ�
		static TaskHandle AddTask(TaskBase* pTask, int priority = 0);

		// �^�X�N�ǉ�(�e�w��)
		static TaskHandle AddTask(TaskHandle pParent, TaskBase* pTask, int priority = 0);

		// �^�X�N�폜
		static void RemoveTask(TaskHandle hTask);

		// ���ׂẴ^�X�N���폜
		static void RemoveTaskAll();

	private:

		struct NodeReserve
		{
			TaskHandle pParent;

			TaskHandle pChild;
		};

	private:

		// �^�X�N�m�[�h�̍���
		static TaskNodeHandle mMasterNode;

		// �ǉ��\��̃m�[�h
		static std::list<NodeReserve> mNodeReserveList;

		// �t���O
		static Utility::Flag mFlag;

	};
}