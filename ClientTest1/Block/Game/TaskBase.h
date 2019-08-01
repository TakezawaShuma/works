#pragma once

#include "TaskManager.h"

namespace Task
{
	class TaskBase
	{
	public:	// 基本処理

		TaskBase();

		virtual ~TaskBase();

		// 開始処理
		virtual void Start() = 0;

		// 更新
		virtual bool Update() = 0;

		virtual bool LastUpdate() { return true; };

		// 描画
		virtual void Draw() {};
		virtual void DrawBegin() {};
		virtual void DrawEnd() {};

		// タスクハンドルの設定
		void SetThisTaskHandle(TaskHandle hTask)
		{
			mhThisTask = hTask;
		}

		// タスクハンドルの取得
		TaskHandle GetThisTaskHandle()
		{
			return mhThisTask;
		}

	private:

		// タスクハンドル
		TaskHandle mhThisTask;

	private:

	};
}