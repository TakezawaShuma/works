// プリコンパイルヘッダ ---------------
#include "../../pch.h"
// ------------------------------------
// シーン関係 -------------------------
#include "TitleScene.h"
#include "../Scene/GameScene.h"
// ------------------------------------
// エフェクト関係 ---------------------
#include "../Effects/EffectManager.h"
// ------------------------------------
// 通信関係 ---------------------------
#include "../../NetworkClient.h"
#include "../NetworkManeger.h"
// ------------------------------------
// その他 -----------------------------
#include "../InputManager.h"		// 入力
#include "../PlayScene/Player.h"	// プレイヤーデータ
// ------------------------------------

using namespace std;
using namespace Utility;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace System;


static const int INPUT_BOX_SIZE_X = 320;
static const int INPUT_BOX_SIZE_Y = 96;
static const int NUMBER_SIZE_X = 16;
static const int NUMBER_SIZE_Y = 32;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_change">シーン切り替えのクラスポインタ</param>
TitleScene::TitleScene(ISceneChange* _change):m_inputIpFlag(false),m_input(nullptr), m_effectType(0),m_ip(""), m_effect(nullptr), m_inputBox(nullptr),m_numbers(nullptr)
{
	m_changeScene = _change;

}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	End();

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="_effect"></param>
void TitleScene::Start(EffectManager* _effect)
{
	// エフェクトの取得と設定
	m_effect = _effect;

	// 入力ボックスのデータ
	m_inputBox = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_inputBox, L"Resources/TitleScene/InputBox.png");
	m_inputBox->SetRect(INPUT_BOX_SIZE_X, INPUT_BOX_SIZE_Y);
	m_inputBox->SetPos(240, 600);

	// 数字の画像データ 
	m_numbers = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_numbers, L"Resources/TitleScene/Number.png");

	// 画像データの取得
	m_effect->LoadTexture(L"Resources/TitleScene/BG.png");
	m_effect->LoadTexture(L"Resources/TitleScene/Title.png");
	m_effect->LoadTexture(L"Resources/TitleScene/Push.png");

	// 入力の取得
	if (m_input == nullptr) m_input = new InputIp();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_timer">時間経過</param>
/// <returns></returns>
bool TitleScene::Update(DX::StepTimer const& _timer)
{
	float timer = (float)_timer.GetTotalSeconds();
	m_effect->Update(timer, SCENE::TITLE, m_effectType);



	// IP入力フラグが立っていないなら
	if (!m_inputIpFlag)
	{
		// 入力準備
		if (InputManager::GetInstance().GetKeyTracker().pressed.Enter)
		{
			m_inputIpFlag = true;
			return true;
		}
		// デバック用(ロビーへ移動)
		else if (InputManager::GetInstance().GetKeyTracker().pressed.L)
		{
			m_changeScene->ChangeScene(SCENE::LOBBY);
			return true;
		}
		// デバック用(プレイシーンへ移動)
		else if (InputManager::GetInstance().GetKeyTracker().pressed.P)
		{
			m_changeScene->ChangeScene(SCENE::PLAY);
			return true;
		}
		// デバック用(リザルトシーンへ移動)
		else if (InputManager::GetInstance().GetKeyTracker().pressed.R)
		{
			m_changeScene->ChangeScene(SCENE::RESULT);
			return true;
		}
	}
	// IP入力フラグが立っているなら
	else
	{
		// 入力されたもの
		char buf = m_input->Input();
		// 入力されていたら
		if (buf != NULL)
		{
			IpEdit(buf);
		}
		
		// 入力完了
		if (InputManager::GetInstance().GetKeyTracker().pressed.Enter)
		{

			// m_ipの中身を空にする
			m_ip.clear();
			// m_testIPの中身をstring型に変換しm_ipに格納
			for (u_int i = 0; i < m_testIp.size(); i++)
			{
				m_ip += std::string::value_type(m_testIp[i]);
			}
			// 自分にアクセス
			if (m_ip == "0000")
			{
				std::string str = "127.0.0.1";
				NetworkClient::GetInstance().IP(str);
				m_changeScene->ChangeScene(SCENE::LOGIN);

				return true;
			}
			// その他の機器にアクセス
			else
			{
				std::string str = "127.0.0.1";
				m_ip += "\0";
				NetworkClient::GetInstance().IP(m_ip);
				//NetworkClient::GetInstance().IP(str.c_str());
				m_changeScene->ChangeScene(SCENE::LOGIN);
				return true;
			}
		}
	}
	return true;
}


/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Draw()
{
	// タイトル＆背景の描画
	if (m_effect != nullptr)
	{
		m_effect->Render(SCENE::TITLE);
	}
	// 入力ボックスや文字の描画
	if (m_inputIpFlag)
	{
		DrawManager::GetInstance().Draw(*m_inputBox);

		// 数字等
		for (u_int i = 0; i < m_IpNum.size(); i++)
		{
			int n = m_IpNum[i] - ',';
			LONG h = n / 4;
			LONG w = n % 4;

			m_numbers->SetRect(NUMBER_SIZE_X * w, NUMBER_SIZE_Y * h, NUMBER_SIZE_X * (w + 1), NUMBER_SIZE_Y * (h + 1));
			m_numbers->SetPos((m_inputBox->GetPos().x + NUMBER_SIZE_Y) + (NUMBER_SIZE_X * i), m_inputBox->GetPos().y + NUMBER_SIZE_Y);
			
			DrawManager::GetInstance().Draw(*m_numbers);
		}
	}
}

/// <summary>
/// タイトルの終了処理
/// </summary>
void TitleScene::End()
{
	m_testIp.clear();
	m_IpNum.clear();

	delete m_input;
	m_input = nullptr;

	delete m_inputBox;
	m_inputBox = nullptr;

	delete m_numbers;
	m_numbers = nullptr;

	if(m_effect) m_effect->LostTexture();
	m_effect = nullptr;
}

/// <summary>
/// IPアドレスの書き換え
/// </summary>
void TitleScene::IpEdit(char _buf)
{
	// BackSpaceが押されたら
	if (_buf == 'b')
	{
		if (m_testIp.size() != 0)
		{
			// 1文字消す
			m_testIp.pop_back();
			m_IpNum.pop_back();
		}
	}
	// deleteが押されたら
	else if (_buf == 'd')
	{
		m_testIp.clear();
		m_IpNum.clear();
	}
	else if (_buf == 'e')
	{

	}
	// それ以外なら
	else
	{
		// 文字を入れる
		m_testIp.push_back(_buf);
		m_IpNum.push_back(_buf);
	}

}

