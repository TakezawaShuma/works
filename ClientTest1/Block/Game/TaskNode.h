#pragma once

#include <list>
#include "Utility\Flag.h"

namespace Task
{

	class TaskBase;
	class TaskNodeHandle;

	class TaskNode
	{
	public:

		TaskNode();

		virtual ~TaskNode();

		int GetPrioryty();

		int GetChildNum() { return mChildTaskList.size(); }

		bool IsFlag(unsigned int flag) { return mFlag.Is(flag); }

	public:

		enum class TaskNodeFlag
		{
			IS_UPDATE			= (1<<0),		// �X�V����
			REMOVE_RESERVE		= (1<<1),		// �폜�\��
		};

	protected:

		// �e�^�X�N
		TaskNodeHandle* mpParentTask;

		// �Ǘ�����^�X�N
		TaskBase* mpWorkTask;

		// �q�̃^�X�N
		std::list<TaskNodeHandle*> mChildTaskList;

		// ���s�D�揇��
		int mPriority;

		// �t���O
		Utility::Flag mFlag;


	};
}