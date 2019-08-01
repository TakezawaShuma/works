#include "../../pch.h"
// シーン -----------------------------
#include "ResultScene.h"
// ------------------------------------
// その他 -----------------------------
#include "../PlayScene/Player.h"
#include "../../Debug.h"
// ------------------------------------
// 入力関係 ---------------------------
#include "../InputManager.h"
// ------------------------------------
using namespace System;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 定数
static const int RANK_SIZE_X = 16;
static const int RANK_SIZE_Y = 32;
static const int RANK_POS_X = 300;
static const int RANK_POS_Y = 250;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_change"></param>
ResultScene::ResultScene(ISceneChange* _change): m_effect(nullptr),m_ranks(nullptr)
{
	m_changeScene = _change;
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	End();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="_effect"></param>
void ResultScene::Start(System::EffectManager* _effect)
{
	m_effect = _effect;

	// 受信
	NetworkManeger::GetInstance().Recv(this);

	m_sendData.socket = NetworkClient::GetInstance().GetMySocket();
	m_sendData.scene = SCENE::RESULT;
	m_sendData.nextScene = SCENE::NON;
	m_sendData.changeSceneFlag = -1;
	// シーンが切り替わったことを報告
	memcpy(m_data, &m_sendData, sizeof(m_data));
	NetworkClient::GetInstance().Send(m_data, sizeof(m_data));


	m_ranks = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_ranks, L"Resources/ResultScene/Number.png");


	if (m_effect != nullptr) m_effect->LoadTexture(L"Resources/ResultScene/BG.png");
	if (m_effect != nullptr) m_effect->LoadTexture(L"Resources/ResultScene/Push.png");
}

/// <summary>
/// 更新
/// </summary>
/// <param name="_timer"></param>
/// <returns></returns>
bool ResultScene::Update(DX::StepTimer const& _timer)
{
	float time = (float)_timer.GetTotalSeconds();
	time;
	if (InputManager::GetInstance().GetKeyTracker().IsKeyPressed(Keyboard::Enter))
	{
		m_changeScene->ChangeScene(SCENE::TITLE);
		return true;
	}
	return true;
}

/// <summary>
/// 描画
/// </summary>
void ResultScene::Draw()
{
	if (m_effect) m_effect->Render(SCENE::RESULT);


	int rank[2];
	rank[0] = m_myData.rank / 10;
	rank[1] = m_myData.rank % 10;
	for (u_int i = 0; i < 2; i++)
	{
		LONG h = rank[i] / 4;
		LONG w = rank[i] % 4;
		m_ranks->SetRect(RANK_SIZE_X * w, RANK_SIZE_Y * h, RANK_SIZE_X * (w + 1), RANK_SIZE_Y * (h + 1));
		m_ranks->SetScale(4,4);
		m_ranks->SetPos(RANK_POS_X + (RANK_SIZE_X * m_ranks->GetScale().x * i),(float) RANK_POS_Y);
		DrawManager::GetInstance().Draw(*m_ranks);
	}
}

/// <summary>
/// 終了
/// </summary>
void ResultScene::End()
{
	if (m_effect) m_effect->LostTexture();
	delete m_ranks; m_ranks = nullptr;
}

/// <summary>
/// 受信コールバック
/// </summary>
/// <param name="_data"></param>
/// <returns></returns>
int ResultScene::Reception(char * _data)
{
	PlayerData p;
	memcpy(&p, _data, sizeof(PlayerData));

	if (p.socket == NetworkClient::GetInstance().GetMySocket())
	{
		m_myData = p;
	}

	return 0;
}
