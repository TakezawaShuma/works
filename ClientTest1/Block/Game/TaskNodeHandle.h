#pragma once

#include "TaskNode.h"

namespace Task
{
	class TaskNodeHandle : public TaskNode
	{
	public:
		TaskNodeHandle(TaskNodeHandle* pParentTask, TaskBase* pWorkTask, int priority);

		~TaskNodeHandle();

		// �J�n����
		void Start();

		// �X�V
		bool Update(bool parentRet);

		// �`��
		void Draw();

		// �q�̒ǉ�
		void AddChildTask(TaskNodeHandle* pChild);

		// �e�̐ݒ�
		void SetParent(TaskNodeHandle* pParent);

		void SortChild();

		// �Ǘ��^�X�N�������q�^�X�N���폜
		void Clean(bool isWorkTaskDelete = false);

		// �Ǘ��^�X�N�̍폜
		void DeleteWarkTask();

		// �q�^�X�N�����ׂč폜
		void DeleteChildAll();

		// �Ǘ��^�X�N�����݂��邩�m�F
		bool IsWorkTask()
		{
			return mpWorkTask != NULL;
		}
	};
}