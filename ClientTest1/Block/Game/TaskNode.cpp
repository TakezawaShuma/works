#include "../pch.h"
#include "TaskBase.h"
#include "TaskNode.h"

using namespace Task;

/// <summary>
/// コンストラクタ
/// </summary>
TaskNode::TaskNode()
	:	mpParentTask(NULL),
		mpWorkTask(NULL),
		mPriority(0)
{

}

/// <summary>
/// デストラクタ
/// </summary>
TaskNode::~TaskNode()
{

}

/// <summary>
/// 優先度の取得
/// </summary>
/// <returns>優先度</returns>
int TaskNode::GetPrioryty()
{
	return mPriority;
}