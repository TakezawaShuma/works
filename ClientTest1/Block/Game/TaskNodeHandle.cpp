#include "../pch.h"
#include "TaskNodeHandle.h"
#include "TaskNode.h"
#include "TaskBase.h"

using namespace Task;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pParentTask">�e</param>
/// <param name="pThisTask">�Ǘ�����^�X�N</param>
/// <param name="priority">���s��</param>
TaskNodeHandle::TaskNodeHandle(TaskNodeHandle* pParentTask, TaskBase* pWorkTask, int priority)
{
	mpParentTask = pParentTask;
	mpWorkTask = pWorkTask;
	mPriority = priority;

	// �Ǘ��^�X�N�����݂���ꍇ�̓^�X�N�n���h����ݒ�
	if (mpWorkTask != NULL)
	{
		mpWorkTask->SetThisTaskHandle(this);
	}

	// �e���w�肳��Ă���ꍇ�͂��̐e�̎q�Ƃ��ēo�^
	if (pParentTask != NULL)
	{
		pParentTask->AddChildTask(this);
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TaskNodeHandle::~TaskNodeHandle()
{
	// �Ǘ��^�X�N�̍폜
	if(mpWorkTask != NULL)
	{
		delete(mpWorkTask);
		mpWorkTask = NULL;
	}

	// �q�����ׂč폜
	DeleteChildAll();

	mChildTaskList.clear();
}

/// <summary>
/// �J�n����
/// </summary>
void TaskNodeHandle::Start()
{
	// �Ǘ��^�X�N�����݂��Ȃ��ꍇ�͏������Ȃ�
	if (mpWorkTask == NULL)
	{
		return;
	}

	mpWorkTask->Start();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="parentRet">�e�̏I�����</param>
/// <returns>�폜���s��ꂽ�� true = �폜����ĂȂ�, false = �폜�폜���ꂽ</returns>
bool TaskNodeHandle::Update(bool parentRet)
{
	// �^�X�N�̏I�����
	bool updateRet = parentRet;
	bool funcRet = true;

	// �Ǘ��^�X�N�����݂���ꍇ�͍X�V����
	if (mpWorkTask != NULL)
	{

		// �e���I����ԂłȂ��ꍇ�̂݊Ǘ��^�X�N�̍X�V
		if (parentRet)
		{
			updateRet = mpWorkTask->Update();
		}

		// �I����Ԃ̏ꍇ�͊Ǘ��^�X�N���폜
		if (!updateRet)
		{
			DeleteWarkTask();
			funcRet = false;
		}
	}

	// �q�^�X�N�̍X�V
	for (std::list<TaskNodeHandle*>::iterator itr = mChildTaskList.begin(); itr != mChildTaskList.end(); ++itr)
	{
		// �X�V����
		bool ret = false;
		ret = (*itr)->Update(updateRet);

		if (funcRet && !ret)
		{
			funcRet = false;
		}
	}

	// �Ǘ��^�X�N�����݂���ꍇ�͍Ō�ɍX�V����
	if (mpWorkTask != NULL)
	{

		// �e���I����ԂłȂ��ꍇ�̂݊Ǘ��^�X�N�̍X�V
		if (parentRet)
		{
			updateRet = mpWorkTask->LastUpdate();
		}

		// �I����Ԃ̏ꍇ�͊Ǘ��^�X�N���폜
		if (!updateRet)
		{
			DeleteWarkTask();
			funcRet = false;
		}
	}

	// �폜���s��ꂽ����Ԃ�
	return funcRet;
}

/// <summary>
/// �`��
/// </summary>
void TaskNodeHandle::Draw()
{
	// �Ǘ��^�X�N�����݂���ꍇ�͕`�揈��
	if (mpWorkTask != NULL)
	{
		// �`��̑O����
		mpWorkTask->DrawBegin();

		// �Ǘ��^�X�N�̍X�V
		mpWorkTask->Draw();
	}

	// �q�^�X�N�̕`��
	for (std::list<TaskNodeHandle*>::iterator itr = mChildTaskList.begin(); itr != mChildTaskList.end(); ++itr)
	{
		(*itr)->Draw();
	}

	if (mpWorkTask != NULL)
	{
		// �`��̌㏈��
		mpWorkTask->DrawEnd();
	}
}

/// <summary>
/// �q�̒ǉ�
/// </summary>
/// <param name="pChild">�ǉ�����q</param>
void TaskNodeHandle::AddChildTask(TaskNodeHandle* pChild)
{
	// NULL�̒ǉ��͔F�߂Ȃ�
	if (pChild == NULL)
	{
		return;
	}

	mChildTaskList.push_back(pChild);

	// �q�̐e�Ɏ��M�̃^�X�N��ݒ�
	SetParent(this);
}

/// <summary>
/// �e�̐ݒ�
/// </summary>
/// <param name="pParent">�e</param>
void Task::TaskNodeHandle::SetParent(TaskNodeHandle * pParent)
{
	mpParentTask = pParent;
}

/// <summary>
/// �q�̃\�[�g
/// </summary>
void TaskNodeHandle::SortChild()
{
	mChildTaskList.sort([](TaskNodeHandle* a, TaskNodeHandle* b) { return a->GetPrioryty() < b->GetPrioryty(); });
}

/// <summary>
/// �Ǘ��^�X�N�̂Ȃ��q���폜
/// </summary>
void TaskNodeHandle::Clean(bool isWorkTaskDelete)
{
	for (std::list<TaskNodeHandle*>::iterator itr = mChildTaskList.begin(); itr != mChildTaskList.end(); )
	{
		// �Ǘ��^�X�N������ꍇ
		if ((*itr)->IsWorkTask())
		{
			// ��ƃ^�X�N�������t���O�������Ă���Ȃ�
			if (isWorkTaskDelete)
			{
				// �폜
				(*itr)->DeleteWarkTask();
			}
			else
			{
				++itr;
				// ����
				continue;
			}
		}

		// �q�̊m�F
		(*itr)->Clean(isWorkTaskDelete);

		// �Ǘ��^�X�N���Ȃ��̂ō폜
		delete((*itr));
		itr = mChildTaskList.erase(itr);
	}
}

/// <summary>
/// �Ǘ��^�X�N�̍폜
/// </summary>
void TaskNodeHandle::DeleteWarkTask()
{
	// �Ǘ��^�X�N���w�肳��Ă��Ȃ��Ȃ珈�����Ȃ�
	if (mpWorkTask == NULL)
	{
		return;
	}

	// �Ǘ��^�X�N�̍폜
	delete(mpWorkTask);

	mpWorkTask = NULL;
}

/// <summary>
/// �q�����ׂč폜
/// </summary>
void TaskNodeHandle::DeleteChildAll()
{
	// �q�̍폜
	for (std::list<TaskNodeHandle*>::iterator itr = mChildTaskList.begin(); itr != mChildTaskList.end(); ++itr)
	{
		(*itr)->DeleteWarkTask();
	}
}
