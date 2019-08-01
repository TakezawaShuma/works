#include "../pch.h"
#include "TaskNodeHandle.h"
#include "TaskNode.h"
#include "TaskBase.h"

using namespace Task;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pParentTask">親</param>
/// <param name="pThisTask">管理するタスク</param>
/// <param name="priority">実行順</param>
TaskNodeHandle::TaskNodeHandle(TaskNodeHandle* pParentTask, TaskBase* pWorkTask, int priority)
{
	mpParentTask = pParentTask;
	mpWorkTask = pWorkTask;
	mPriority = priority;

	// 管理タスクが存在する場合はタスクハンドルを設定
	if (mpWorkTask != NULL)
	{
		mpWorkTask->SetThisTaskHandle(this);
	}

	// 親が指定されている場合はその親の子として登録
	if (pParentTask != NULL)
	{
		pParentTask->AddChildTask(this);
	}
}

/// <summary>
/// デストラクタ
/// </summary>
TaskNodeHandle::~TaskNodeHandle()
{
	// 管理タスクの削除
	if(mpWorkTask != NULL)
	{
		delete(mpWorkTask);
		mpWorkTask = NULL;
	}

	// 子をすべて削除
	DeleteChildAll();

	mChildTaskList.clear();
}

/// <summary>
/// 開始処理
/// </summary>
void TaskNodeHandle::Start()
{
	// 管理タスクが存在しない場合は処理しない
	if (mpWorkTask == NULL)
	{
		return;
	}

	mpWorkTask->Start();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="parentRet">親の終了状態</param>
/// <returns>削除が行われたか true = 削除されてない, false = 削除削除された</returns>
bool TaskNodeHandle::Update(bool parentRet)
{
	// タスクの終了状態
	bool updateRet = parentRet;
	bool funcRet = true;

	// 管理タスクが存在する場合は更新処理
	if (mpWorkTask != NULL)
	{

		// 親が終了状態でない場合のみ管理タスクの更新
		if (parentRet)
		{
			updateRet = mpWorkTask->Update();
		}

		// 終了状態の場合は管理タスクを削除
		if (!updateRet)
		{
			DeleteWarkTask();
			funcRet = false;
		}
	}

	// 子タスクの更新
	for (std::list<TaskNodeHandle*>::iterator itr = mChildTaskList.begin(); itr != mChildTaskList.end(); ++itr)
	{
		// 更新処理
		bool ret = false;
		ret = (*itr)->Update(updateRet);

		if (funcRet && !ret)
		{
			funcRet = false;
		}
	}

	// 管理タスクが存在する場合は最後に更新処理
	if (mpWorkTask != NULL)
	{

		// 親が終了状態でない場合のみ管理タスクの更新
		if (parentRet)
		{
			updateRet = mpWorkTask->LastUpdate();
		}

		// 終了状態の場合は管理タスクを削除
		if (!updateRet)
		{
			DeleteWarkTask();
			funcRet = false;
		}
	}

	// 削除が行われたかを返す
	return funcRet;
}

/// <summary>
/// 描画
/// </summary>
void TaskNodeHandle::Draw()
{
	// 管理タスクが存在する場合は描画処理
	if (mpWorkTask != NULL)
	{
		// 描画の前処理
		mpWorkTask->DrawBegin();

		// 管理タスクの更新
		mpWorkTask->Draw();
	}

	// 子タスクの描画
	for (std::list<TaskNodeHandle*>::iterator itr = mChildTaskList.begin(); itr != mChildTaskList.end(); ++itr)
	{
		(*itr)->Draw();
	}

	if (mpWorkTask != NULL)
	{
		// 描画の後処理
		mpWorkTask->DrawEnd();
	}
}

/// <summary>
/// 子の追加
/// </summary>
/// <param name="pChild">追加する子</param>
void TaskNodeHandle::AddChildTask(TaskNodeHandle* pChild)
{
	// NULLの追加は認めない
	if (pChild == NULL)
	{
		return;
	}

	mChildTaskList.push_back(pChild);

	// 子の親に自信のタスクを設定
	SetParent(this);
}

/// <summary>
/// 親の設定
/// </summary>
/// <param name="pParent">親</param>
void Task::TaskNodeHandle::SetParent(TaskNodeHandle * pParent)
{
	mpParentTask = pParent;
}

/// <summary>
/// 子のソート
/// </summary>
void TaskNodeHandle::SortChild()
{
	mChildTaskList.sort([](TaskNodeHandle* a, TaskNodeHandle* b) { return a->GetPrioryty() < b->GetPrioryty(); });
}

/// <summary>
/// 管理タスクのない子を削除
/// </summary>
void TaskNodeHandle::Clean(bool isWorkTaskDelete)
{
	for (std::list<TaskNodeHandle*>::iterator itr = mChildTaskList.begin(); itr != mChildTaskList.end(); )
	{
		// 管理タスクがある場合
		if ((*itr)->IsWorkTask())
		{
			// 作業タスクを消すフラグが立っているなら
			if (isWorkTaskDelete)
			{
				// 削除
				(*itr)->DeleteWarkTask();
			}
			else
			{
				++itr;
				// 次へ
				continue;
			}
		}

		// 子の確認
		(*itr)->Clean(isWorkTaskDelete);

		// 管理タスクがないので削除
		delete((*itr));
		itr = mChildTaskList.erase(itr);
	}
}

/// <summary>
/// 管理タスクの削除
/// </summary>
void TaskNodeHandle::DeleteWarkTask()
{
	// 管理タスクが指定されていないなら処理しない
	if (mpWorkTask == NULL)
	{
		return;
	}

	// 管理タスクの削除
	delete(mpWorkTask);

	mpWorkTask = NULL;
}

/// <summary>
/// 子をすべて削除
/// </summary>
void TaskNodeHandle::DeleteChildAll()
{
	// 子の削除
	for (std::list<TaskNodeHandle*>::iterator itr = mChildTaskList.begin(); itr != mChildTaskList.end(); ++itr)
	{
		(*itr)->DeleteWarkTask();
	}
}
