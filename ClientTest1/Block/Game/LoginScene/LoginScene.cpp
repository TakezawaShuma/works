#include "../../pch.h"
// シーン -----------------------------
#include "LoginScene.h"
#include "../TitleScene/TitleScene.h"
#include "../LobbyScene/LobbyScene.h"
// ------------------------------------
// 通信関係 ---------------------------
#include "../../NetworkClient.h"
#include "../NetworkManeger.h"
// ------------------------------------
// その他 -----------------------------
//#include "../PlayScene/Player.h"
// ------------------------------------

using namespace System;

/// <summary>
///	コンストラクタ
/// </summary>
/// <param name="_changeScene"></param>
LoginScene::LoginScene(ISceneChange * _changeScene):m_uiManager(nullptr),m_effect(nullptr)
{
	m_changeScene = _changeScene;
}

/// <summary>
/// デストラクタ
/// </summary>
LoginScene::~LoginScene()
{
	End();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="_effect"></param>
void LoginScene::Start(EffectManager* _effect)
{
	timer = 0;
	m_effect = _effect;
	const char* c = NetworkClient::GetInstance().IP();

	if (m_uiManager == nullptr) m_uiManager = new UIManeger();
	if (m_uiManager != nullptr)	m_uiManager->Start(SCENE::LOGIN);
	if (!NetworkClient::GetInstance().Connect(c, PORT)) 
	{ 
		return;
	}

}

/// <summary>
/// 更新
/// </summary>
/// <param name="_timer"></param>
/// <returns></returns>
bool LoginScene::Update(DX::StepTimer const& _timer)
{
	float time = (float)_timer.GetTotalSeconds();
	time;

	// ログインしたかどうかの情報の受け取り
	SOCKET soc = NetworkManeger::GetInstance().Recv();

	m_effect->Update(time, SCENE::LOGIN, 0);
	if (m_uiManager != nullptr) m_uiManager->Update();


	// ログインしていたら
	if (soc != 0)
	{
		//自身のソケットを登録
		NetworkClient::GetInstance().SetMySocket(soc);
		// 登録後シーン切り替え
		m_changeScene->ChangeScene(SCENE::LOBBY);
		return true;
	}
	else { timer++; }

	// 一定時間ログインできなかったらタイトルへ戻る
	if (timer > 300)
	{
		m_changeScene->ChangeScene(SCENE::TITLE);
	}
	return true;
}

/// <summary>
/// 描画
/// </summary>
void LoginScene::Draw()
{
	m_effect->Render(SCENE::LOGIN);
	if (m_uiManager != nullptr)	m_uiManager->Render(UIType::NowConnection, 0);
}

/// <summary>
/// 終了
/// </summary>
void LoginScene::End()
{
	if (m_effect->TextureListSize() != 0) { m_effect->LostTexture(); }
	m_uiManager->End();
	delete m_uiManager;	m_uiManager = nullptr;
}

