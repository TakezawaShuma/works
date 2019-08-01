#include "../pch.h"
#include "TaskManager.h"
#include "TaskBase.h"
#include "TaskNode.h"
#include "TaskNodeHandle.h"

using namespace Task;

// マスターノード
TaskNodeHandle TaskManager::mMasterNode(NULL, NULL, 0);

// 追加予定の子リスト
std::list<TaskManager::NodeReserve> TaskManager::mNodeReserveList;

// フラグ
Utility::Flag TaskManager::mFlag;

/// <summary>
/// タスク追加
/// </summary>
/// <param name="pTask">管理するタスク</param>
/// <param name="priority">実行順</param>
/// <returns>タスクハンドル</returns>
TaskHandle TaskManager::AddTask(TaskBase* pTask, int priority)
{
	return AddTask(&mMasterNode, pTask, priority);
}

/// <summary>
/// タスク追加(親指定)
/// </summary>
/// <param name="pParent">親</param>
/// <param name="pTask">管理するタスク</param>
/// <param name="priority">実行順</param>
/// <returns>タスクハンドル</returns>
TaskHandle TaskManager::AddTask(TaskHandle pParent, TaskBase* pTask, int priority)
{
	if (pTask == NULL)
	{
		return NULL;
	}

	// タスクノードハンドルの作成
	TaskNodeHandle* pNodeHandle = new TaskNodeHandle(NULL, pTask, priority);

	// 追加タスク情報を予約リストに追加
	NodeReserve r;
	r.pParent = pParent;
	r.pChild = pNodeHandle;

	mNodeReserveList.push_back(r);

	return pNodeHandle;
}

/// <summary>
/// タスク削除
/// </summary>
/// <param name="hTask">削除したいタスク</param>
void TaskManager::RemoveTask(TaskHandle hTask)
{
	// キャスト
	TaskNodeHandle* pNodeHandle = dynamic_cast<TaskNodeHandle*>(hTask);

	// キャストに失敗したら処理しない
	if (pNodeHandle == NULL)
	{
		return;
	}

	// 管理タスクの削除
	pNodeHandle->DeleteWarkTask();

	// 削除フラグを立てる
	mFlag.On(eTaskManagerFlag::IsDeleted);
}

/// <summary>
/// タスクをすべて削除
/// </summary>
void TaskManager::RemoveTaskAll()
{
	mMasterNode.DeleteChildAll();

	mFlag.On(eTaskManagerFlag::IsDeleted);
}

/// <summary>
/// コンストラクタ
/// </summary>
TaskManager::TaskManager()
{

}

/// <summary>
/// デストラクタ
/// </summary>
TaskManager::~TaskManager()
{

}

/// <summary>
/// 更新
/// </summary>
void TaskManager::Update()
{
	bool ret = false;
	ret = mMasterNode.Update(true);

	if (!ret)
	{
		// 削除フラグを立てる
		mFlag.On(eTaskManagerFlag::IsDeleted);
	}
}

/// <summary>
/// 描画
/// </summary>
void TaskManager::Draw()
{
	mMasterNode.Draw();
}

/// <summary>
/// 不要タスクの削除
/// </summary>
void TaskManager::CleanTask(bool isWorkTaskDelete)
{
	// 削除フラグが立っていない場合は処理しない
	if (!(mFlag.Is(eTaskManagerFlag::IsDeleted)))
	{
		return;
	}

	// 不要タスクの削除
	mMasterNode.Clean(isWorkTaskDelete);

	// 削除フラグを伏せる
	mFlag.Off(eTaskManagerFlag::IsDeleted);
}

/// <summary>
/// 予約リストのタスクを追加する
/// </summary>
void TaskManager::AddReserve()
{
	// 追加予約がないなら処理しない
	if (mNodeReserveList.size() == 0)
	{
		return;
	}

	// 子が追加されたタスクの保存
	std::list<TaskNodeHandle*> parentList;

	// 追加完了したタスクのリスト
	std::list<TaskNodeHandle*> addTaskList;

	for (auto it = mNodeReserveList.begin(); it != mNodeReserveList.end(); it++)
	{
		// 親と子をキャスト
		TaskNodeHandle* pParent = dynamic_cast<TaskNodeHandle*>((*it).pParent);
		TaskNodeHandle* pChild = dynamic_cast<TaskNodeHandle*>((*it).pChild);

		// 例外は処理しない
		if (pParent == NULL || pChild == NULL)
		{
			// 親が無く子タスクのみが作られている場合は子を削除
			if (pChild != NULL)
			{
				pChild->DeleteWarkTask();
				delete(pChild);
			}

			continue;
		}

		// 子を親へと正式に追加
		pParent->AddChildTask(pChild);

		// 追加された事実を保存
		parentList.push_back(pParent);

		// 追加完了した子タスクを保存
		addTaskList.push_back(pChild);
	}

	// 追加成功した親リストの重複項目を削除
	parentList.unique();

	// 子が追加された親タスクの子リストをソート
	for (auto it = parentList.begin(); it != parentList.end(); it++)
	{
		if ((*it) == NULL)
		{
			continue;
		}

		(*it)->SortChild();
	}

	// 予約リストを削除
	mNodeReserveList.clear();

	// 追加したタスクのstart関数を呼び出し
	for (auto it = addTaskList.begin(); it != addTaskList.end(); it++)
	{
		// Start関数の呼び出し
		(*it)->Start();
	}

	// 予約リストがまた復活した場合は処理
	AddReserve();
}