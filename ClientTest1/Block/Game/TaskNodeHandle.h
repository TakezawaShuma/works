#pragma once

#include "TaskNode.h"

namespace Task
{
	class TaskNodeHandle : public TaskNode
	{
	public:
		TaskNodeHandle(TaskNodeHandle* pParentTask, TaskBase* pWorkTask, int priority);

		~TaskNodeHandle();

		// 開始処理
		void Start();

		// 更新
		bool Update(bool parentRet);

		// 描画
		void Draw();

		// 子の追加
		void AddChildTask(TaskNodeHandle* pChild);

		// 親の設定
		void SetParent(TaskNodeHandle* pParent);

		void SortChild();

		// 管理タスクが無い子タスクを削除
		void Clean(bool isWorkTaskDelete = false);

		// 管理タスクの削除
		void DeleteWarkTask();

		// 子タスクをすべて削除
		void DeleteChildAll();

		// 管理タスクが存在するか確認
		bool IsWorkTask()
		{
			return mpWorkTask != NULL;
		}
	};
}