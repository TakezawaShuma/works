#include "../pch.h"
#include "TaskBase.h"
#include "TaskNode.h"

using namespace Task;

/// <summary>
/// �R���X�g���N�^
/// </summary>
TaskNode::TaskNode()
	:	mpParentTask(NULL),
		mpWorkTask(NULL),
		mPriority(0)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TaskNode::~TaskNode()
{

}

/// <summary>
/// �D��x�̎擾
/// </summary>
/// <returns>�D��x</returns>
int TaskNode::GetPrioryty()
{
	return mPriority;
}