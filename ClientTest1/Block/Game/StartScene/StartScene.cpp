#include "../../pch.h"
#include "StartScene.h"
#include "../PlayScene/PlayScene.h"
#include "../TitleScene/TitleScene.h"
#include "../Scene/GameScene.h"


using namespace MyGame;

/// <summary>
/// �R���X�g���N�^
/// </summary>
StartScene::StartScene(System::EffectManager* _effect):m_effect(nullptr)
{
	m_effect = _effect;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StartScene::~StartScene()
{

}

/// <summary>
/// 
/// </summary>
void StartScene::Start()
{
	// �Q�[���̃V�[����ǉ�
	GameScene* pScene = new GameScene(m_effect);
	Task::TaskManager::AddTask(pScene, 0);

}

/// <summary>
/// �X�V
/// </summary>
/// <returns></returns>
bool StartScene::Update()
{
	// ���^�X�N�̍폜
	return false;
}