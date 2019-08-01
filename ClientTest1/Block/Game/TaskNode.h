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
			IS_UPDATE			= (1<<0),		// 更新中か
			REMOVE_RESERVE		= (1<<1),		// 削除予約
		};

	protected:

		// 親タスク
		TaskNodeHandle* mpParentTask;

		// 管理するタスク
		TaskBase* mpWorkTask;

		// 子のタスク
		std::list<TaskNodeHandle*> mChildTaskList;

		// 実行優先順位
		int mPriority;

		// フラグ
		Utility::Flag mFlag;


	};
}