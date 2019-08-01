#include "../pch.h"
#include "TaskManager.h"
#include "TaskBase.h"
#include "TaskNode.h"
#include "TaskNodeHandle.h"

using namespace Task;

// �}�X�^�[�m�[�h
TaskNodeHandle TaskManager::mMasterNode(NULL, NULL, 0);

// �ǉ��\��̎q���X�g
std::list<TaskManager::NodeReserve> TaskManager::mNodeReserveList;

// �t���O
Utility::Flag TaskManager::mFlag;

/// <summary>
/// �^�X�N�ǉ�
/// </summary>
/// <param name="pTask">�Ǘ�����^�X�N</param>
/// <param name="priority">���s��</param>
/// <returns>�^�X�N�n���h��</returns>
TaskHandle TaskManager::AddTask(TaskBase* pTask, int priority)
{
	return AddTask(&mMasterNode, pTask, priority);
}

/// <summary>
/// �^�X�N�ǉ�(�e�w��)
/// </summary>
/// <param name="pParent">�e</param>
/// <param name="pTask">�Ǘ�����^�X�N</param>
/// <param name="priority">���s��</param>
/// <returns>�^�X�N�n���h��</returns>
TaskHandle TaskManager::AddTask(TaskHandle pParent, TaskBase* pTask, int priority)
{
	if (pTask == NULL)
	{
		return NULL;
	}

	// �^�X�N�m�[�h�n���h���̍쐬
	TaskNodeHandle* pNodeHandle = new TaskNodeHandle(NULL, pTask, priority);

	// �ǉ��^�X�N����\�񃊃X�g�ɒǉ�
	NodeReserve r;
	r.pParent = pParent;
	r.pChild = pNodeHandle;

	mNodeReserveList.push_back(r);

	return pNodeHandle;
}

/// <summary>
/// �^�X�N�폜
/// </summary>
/// <param name="hTask">�폜�������^�X�N</param>
void TaskManager::RemoveTask(TaskHandle hTask)
{
	// �L���X�g
	TaskNodeHandle* pNodeHandle = dynamic_cast<TaskNodeHandle*>(hTask);

	// �L���X�g�Ɏ��s�����珈�����Ȃ�
	if (pNodeHandle == NULL)
	{
		return;
	}

	// �Ǘ��^�X�N�̍폜
	pNodeHandle->DeleteWarkTask();

	// �폜�t���O�𗧂Ă�
	mFlag.On(eTaskManagerFlag::IsDeleted);
}

/// <summary>
/// �^�X�N�����ׂč폜
/// </summary>
void TaskManager::RemoveTaskAll()
{
	mMasterNode.DeleteChildAll();

	mFlag.On(eTaskManagerFlag::IsDeleted);
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
TaskManager::TaskManager()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TaskManager::~TaskManager()
{

}

/// <summary>
/// �X�V
/// </summary>
void TaskManager::Update()
{
	bool ret = false;
	ret = mMasterNode.Update(true);

	if (!ret)
	{
		// �폜�t���O�𗧂Ă�
		mFlag.On(eTaskManagerFlag::IsDeleted);
	}
}

/// <summary>
/// �`��
/// </summary>
void TaskManager::Draw()
{
	mMasterNode.Draw();
}

/// <summary>
/// �s�v�^�X�N�̍폜
/// </summary>
void TaskManager::CleanTask(bool isWorkTaskDelete)
{
	// �폜�t���O�������Ă��Ȃ��ꍇ�͏������Ȃ�
	if (!(mFlag.Is(eTaskManagerFlag::IsDeleted)))
	{
		return;
	}

	// �s�v�^�X�N�̍폜
	mMasterNode.Clean(isWorkTaskDelete);

	// �폜�t���O�𕚂���
	mFlag.Off(eTaskManagerFlag::IsDeleted);
}

/// <summary>
/// �\�񃊃X�g�̃^�X�N��ǉ�����
/// </summary>
void TaskManager::AddReserve()
{
	// �ǉ��\�񂪂Ȃ��Ȃ珈�����Ȃ�
	if (mNodeReserveList.size() == 0)
	{
		return;
	}

	// �q���ǉ����ꂽ�^�X�N�̕ۑ�
	std::list<TaskNodeHandle*> parentList;

	// �ǉ����������^�X�N�̃��X�g
	std::list<TaskNodeHandle*> addTaskList;

	for (auto it = mNodeReserveList.begin(); it != mNodeReserveList.end(); it++)
	{
		// �e�Ǝq���L���X�g
		TaskNodeHandle* pParent = dynamic_cast<TaskNodeHandle*>((*it).pParent);
		TaskNodeHandle* pChild = dynamic_cast<TaskNodeHandle*>((*it).pChild);

		// ��O�͏������Ȃ�
		if (pParent == NULL || pChild == NULL)
		{
			// �e�������q�^�X�N�݂̂�����Ă���ꍇ�͎q���폜
			if (pChild != NULL)
			{
				pChild->DeleteWarkTask();
				delete(pChild);
			}

			continue;
		}

		// �q��e�ւƐ����ɒǉ�
		pParent->AddChildTask(pChild);

		// �ǉ����ꂽ������ۑ�
		parentList.push_back(pParent);

		// �ǉ����������q�^�X�N��ۑ�
		addTaskList.push_back(pChild);
	}

	// �ǉ����������e���X�g�̏d�����ڂ��폜
	parentList.unique();

	// �q���ǉ����ꂽ�e�^�X�N�̎q���X�g���\�[�g
	for (auto it = parentList.begin(); it != parentList.end(); it++)
	{
		if ((*it) == NULL)
		{
			continue;
		}

		(*it)->SortChild();
	}

	// �\�񃊃X�g���폜
	mNodeReserveList.clear();

	// �ǉ������^�X�N��start�֐����Ăяo��
	for (auto it = addTaskList.begin(); it != addTaskList.end(); it++)
	{
		// Start�֐��̌Ăяo��
		(*it)->Start();
	}

	// �\�񃊃X�g���܂����������ꍇ�͏���
	AddReserve();
}