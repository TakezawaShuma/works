#include "pch.h"
#include "Debug.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="devise">デバイス</param>
void Debug::Initialize(ID3D11Device1* pDevise, ID3D11DeviceContext1* pContext)
{
	Devise(pDevise);
	m_spriteBatch = std::make_unique<SpriteBatch>(pContext);
	m_spriteFont = make_unique<SpriteFont>(pDevise, L"Resources\\Font\\myfile.spritefont");
	
}

/// <summary>
/// デバック用描画(フロント文字, 数値, バック文字, 表示位置X, 表示位置Y)
/// </summary>
/// <param name="_flontStr">フロント文字</param>
/// <param name="_num">数値</param>
/// <param name="_backStr">バック文字</param>
/// <param name="_x">表示位置X</param>
/// <param name="_y">表示位置Y</param>
void Debug::DebugDraw(std::string _flontStr, int _num, std::string _backStr, float _x, float _y)
{
	wchar_t tmp[100];

	string s = to_string(_num);
	string ok = _flontStr + s + _backStr;
	const char* str = ok.data();

	size_t wLenght = 0;
	errno_t err = 0;

	// ロケール指定
	setlocale(LC_ALL, "Japanese");

	//変換
	err = mbstowcs_s(&wLenght, tmp, 20, str, _TRUNCATE);
	if (err == 0)
	{
		m_spriteBatch->Begin();
		m_spriteFont->DrawString(m_spriteBatch.get(), tmp, Vector2(_x, _y));
		m_spriteBatch->End();
	}
}

void Debug::DebugDraw(std::string _str, float _x, float _y)
{
	wchar_t tmp[100];
	string ok = _str;
	const char* str = ok.data();

	size_t wLenght = 0;
	errno_t err = 0;

	// ロケール指定
	setlocale(LC_ALL, "Japanese");

	//変換
	err = mbstowcs_s(&wLenght, tmp, 20, str, _TRUNCATE);
	if (err == 0)
	{
		m_spriteBatch->Begin();
		m_spriteFont->DrawString(m_spriteBatch.get(), tmp, Vector2(_x, _y));
		m_spriteBatch->End();
	}
}
