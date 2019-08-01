#include "pch.h"
#include "Debug.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// ����������
/// </summary>
/// <param name="devise">�f�o�C�X</param>
void Debug::Initialize(ID3D11Device1* pDevise, ID3D11DeviceContext1* pContext)
{
	Devise(pDevise);
	m_spriteBatch = std::make_unique<SpriteBatch>(pContext);
	m_spriteFont = make_unique<SpriteFont>(pDevise, L"Resources\\Font\\myfile.spritefont");
	
}

/// <summary>
/// �f�o�b�N�p�`��(�t�����g����, ���l, �o�b�N����, �\���ʒuX, �\���ʒuY)
/// </summary>
/// <param name="_flontStr">�t�����g����</param>
/// <param name="_num">���l</param>
/// <param name="_backStr">�o�b�N����</param>
/// <param name="_x">�\���ʒuX</param>
/// <param name="_y">�\���ʒuY</param>
void Debug::DebugDraw(std::string _flontStr, int _num, std::string _backStr, float _x, float _y)
{
	wchar_t tmp[100];

	string s = to_string(_num);
	string ok = _flontStr + s + _backStr;
	const char* str = ok.data();

	size_t wLenght = 0;
	errno_t err = 0;

	// ���P�[���w��
	setlocale(LC_ALL, "Japanese");

	//�ϊ�
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

	// ���P�[���w��
	setlocale(LC_ALL, "Japanese");

	//�ϊ�
	err = mbstowcs_s(&wLenght, tmp, 20, str, _TRUNCATE);
	if (err == 0)
	{
		m_spriteBatch->Begin();
		m_spriteFont->DrawString(m_spriteBatch.get(), tmp, Vector2(_x, _y));
		m_spriteBatch->End();
	}
}
