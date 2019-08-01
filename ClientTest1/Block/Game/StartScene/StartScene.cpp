#include "../../pch.h"
#include "StartScene.h"
#include "../PlayScene/PlayScene.h"
#include "../TitleScene/TitleScene.h"
#include "../Scene/GameScene.h"


using namespace MyGame;

/// <summary>
/// コンストラクタ
/// </summary>
StartScene::StartScene(System::EffectManager* _effect):m_effect(nullptr)
{
	m_effect = _effect;
}

/// <summary>
/// デストラクタ
/// </summary>
StartScene::~StartScene()
{

}

/// <summary>
/// 
/// </summary>
void StartScene::Start()
{
	// ゲームのシーンを追加
	GameScene* pScene = new GameScene(m_effect);
	Task::TaskManager::AddTask(pScene, 0);

}

/// <summary>
/// 更新
/// </summary>
/// <returns></returns>
bool StartScene::Update()
{
	// 自タスクの削除
	return false;
}