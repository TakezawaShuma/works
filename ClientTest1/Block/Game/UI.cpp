// プリコンパイル済ヘッダ -------------
#include "../../pch.h"
// ------------------------------------
// 継承元 -----------------------------
#include "GameObject.h"
// ------------------------------------
#include "UI.h"

const static int HP_SIZE = 32;
const static int CONNECT_SIZE_X = 416;
const static int CONNECT_SIZE_Y = 64;

/// <summary>
/// コンストラクタ
/// </summary>
UI::UI()
{
}

/// <summary>
/// デストラクタ
/// </summary>
UI::~UI()
{
}

/// <summary>
/// UIの初期化
/// </summary>
void UI::Start()
{
}

/// <summary>
/// UIの初期化
/// </summary>
/// <param name="_type"></param>
void UI::StartUI(UIType _type)
{
	// 数が増えたらswitchの方が良い
	if (_type == UIType::HP)
	{
		HpStart();
	}
	else if (_type == UIType::NowConnection)
	{
		ConnectStart();
	}
}

/// <summary>
/// UIの初期化
/// </summary>
void UI::Update()
{


}

/// <summary>
/// UIの描画
/// </summary>
void UI::Draw()
{
}

/// <summary>
/// UIの描画
/// </summary>
/// <param name="_num"></param>
void UI::DrawUI(UIType _type, int _num)
{
	switch (_type)
	{
	case NowConnection:
		System::DrawManager::GetInstance().Draw(m_data);
		break;
	case HP:
		for (int i = 0; i < _num; i++)
		{
			m_data.SetPos((float)HP_SIZE*i + 30.0f, (float)HP_SIZE);
			System::DrawManager::GetInstance().Draw(m_data);
		}
		break;
	case MaxNum:
		break;
	default:
		break;
	}
}

/// <summary>
/// 終了
/// </summary>
void UI::End()
{
	
}

/// <summary>
/// HPのUIを初期化する
/// </summary>
void UI::HpStart()
{
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources/PlayScene/UI/HP.png");
	m_data.SetRect(HP_SIZE, HP_SIZE);
}

/// <summary>
/// コネクトUIの初期化
/// </summary>
void UI::ConnectStart()
{
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources/LoginScene/UI/NowConnecting.png");
	m_data.SetRect(CONNECT_SIZE_X, CONNECT_SIZE_Y);
	m_data.SetPos(800 - CONNECT_SIZE_X, 800 - CONNECT_SIZE_Y);
}

void UI::Frame1Start()
{
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources/LobbyLounge/UI/Frame.png");
	m_data.SetRect(600, 64);
}
void UI::Frame2Start()
{
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources/LobbyLounge/UI/Frame2.png");
	m_data.SetRect(600, 64);
}
