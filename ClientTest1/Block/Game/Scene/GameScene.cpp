#include "../../pch.h"
#include "GameScene.h"
#include "../DrawManager.h"
#include "../InputManager.h"
#include "../../NetworkClient.h"
#include "../NetworkManeger.h"
#include "SceneState.h"



#include "../TitleScene/TitleScene.h"
#include "../LobbyScene/LobbyScene.h"
#include "../PlayScene/PlayScene.h"
#include "../ResultScene/ResultScene.h"
#include "../LoginScene/LoginScene.h"
#include "../../DeviceResources.h"

using namespace DirectX;

extern void ExitGame();

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_effectManager"></param>
GameScene::GameScene(System::EffectManager* _effectManager):m_activeScene(nullptr),m_effectManager(nullptr)
{
	m_effectManager = _effectManager;
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	m_effectManager = nullptr;
	delete m_activeScene;
	m_activeScene = nullptr;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Start()
{
	ChangeScene(SCENE::TITLE);
}

/// <summary>
/// ゲーム更新
/// </summary>
/// <returns></returns>
bool GameScene::Update()
{
	bool ret = true;
	m_timer.Tick([&]()
	{
		ret = Execution(m_timer);
	});
	return ret;
}

/// <summary>
/// ゲーム内容実行
/// </summary>
/// <param name="_timer"></param>
/// <returns></returns>
bool GameScene::Execution(DX::StepTimer const& _timer)
{
	Keyboard::State keyState = Keyboard::Get().GetState();

	if (keyState.Escape)
	{
		ExitGame();
		return false;
	}

	if (m_activeScene != nullptr)
	{
		m_activeScene->Update(_timer);
	}
	else
	{
		return false;
	}
	return true;
}

/// <summary>
/// ゲームの描画処理
/// </summary>
void GameScene::Draw()
{
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	if (m_activeScene != nullptr)
	{
		m_activeScene->Draw();
	}
}

void GameScene::DrawBegin()
{
	System::DrawManager::GetInstance().Begin();
}

void GameScene::DrawEnd()
{
	System::DrawManager::GetInstance().End();
}

void GameScene::ChangeScene(SCENE _nextScene)
{
	if (_nextScene != SCENE::NON)
	{
		if (m_activeScene != nullptr)
		{
			//m_activeScene->End();
			delete m_activeScene;
			m_activeScene = nullptr;
		}
		m_activeScene = CreateScene(_nextScene);
/*
		switch (_nextScene)
		{
		case LOGIN:
			m_activeScene = new LoginScene(this);
			break;

		case TITLE:
			m_activeScene = new TitleScene(this);
			break;

		case LOBBY:
			m_activeScene = new LobbyScene(this);
			break;

		case PLAY:
			m_activeScene = new PlayScene(this);
			break;

		case RESULT:
			m_activeScene = new ResultScene(this);
			break;

		case LOGOUT:
			break;

		default:
			break;
		}*/
		m_activeScene->Start(m_effectManager);
	}
}


SceneState* GameScene::CreateScene(SCENE _nextScene)
{
	SceneState* sceneState = nullptr;
	switch (_nextScene)
	{
	case LOGIN:
		sceneState = new LoginScene(this);
		break;

	case TITLE:
		sceneState = new TitleScene(this);
		break;

	case LOBBY:
		sceneState = new LobbyScene(this);
		break;

	case PLAY:
		sceneState = new PlayScene(this);
		break;

	case RESULT:
		sceneState = new ResultScene(this);
		break;

	case LOGOUT:
		sceneState = nullptr;
		break;

	default:
		break;
	}
	return sceneState;

}


