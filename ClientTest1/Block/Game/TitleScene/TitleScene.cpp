// �v���R���p�C���w�b�_ ---------------
#include "../../pch.h"
// ------------------------------------
// �V�[���֌W -------------------------
#include "TitleScene.h"
#include "../Scene/GameScene.h"
// ------------------------------------
// �G�t�F�N�g�֌W ---------------------
#include "../Effects/EffectManager.h"
// ------------------------------------
// �ʐM�֌W ---------------------------
#include "../../NetworkClient.h"
#include "../NetworkManeger.h"
// ------------------------------------
// ���̑� -----------------------------
#include "../InputManager.h"		// ����
#include "../PlayScene/Player.h"	// �v���C���[�f�[�^
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
/// �R���X�g���N�^
/// </summary>
/// <param name="_change">�V�[���؂�ւ��̃N���X�|�C���^</param>
TitleScene::TitleScene(ISceneChange* _change):m_inputIpFlag(false),m_input(nullptr), m_effectType(0),m_ip(""), m_effect(nullptr), m_inputBox(nullptr),m_numbers(nullptr)
{
	m_changeScene = _change;

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	End();

}

/// <summary>
/// ������
/// </summary>
/// <param name="_effect"></param>
void TitleScene::Start(EffectManager* _effect)
{
	// �G�t�F�N�g�̎擾�Ɛݒ�
	m_effect = _effect;

	// ���̓{�b�N�X�̃f�[�^
	m_inputBox = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_inputBox, L"Resources/TitleScene/InputBox.png");
	m_inputBox->SetRect(INPUT_BOX_SIZE_X, INPUT_BOX_SIZE_Y);
	m_inputBox->SetPos(240, 600);

	// �����̉摜�f�[�^ 
	m_numbers = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_numbers, L"Resources/TitleScene/Number.png");

	// �摜�f�[�^�̎擾
	m_effect->LoadTexture(L"Resources/TitleScene/BG.png");
	m_effect->LoadTexture(L"Resources/TitleScene/Title.png");
	m_effect->LoadTexture(L"Resources/TitleScene/Push.png");

	// ���͂̎擾
	if (m_input == nullptr) m_input = new InputIp();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_timer">���Ԍo��</param>
/// <returns></returns>
bool TitleScene::Update(DX::StepTimer const& _timer)
{
	float timer = (float)_timer.GetTotalSeconds();
	m_effect->Update(timer, SCENE::TITLE, m_effectType);



	// IP���̓t���O�������Ă��Ȃ��Ȃ�
	if (!m_inputIpFlag)
	{
		// ���͏���
		if (InputManager::GetInstance().GetKeyTracker().pressed.Enter)
		{
			m_inputIpFlag = true;
			return true;
		}
		// �f�o�b�N�p(���r�[�ֈړ�)
		else if (InputManager::GetInstance().GetKeyTracker().pressed.L)
		{
			m_changeScene->ChangeScene(SCENE::LOBBY);
			return true;
		}
		// �f�o�b�N�p(�v���C�V�[���ֈړ�)
		else if (InputManager::GetInstance().GetKeyTracker().pressed.P)
		{
			m_changeScene->ChangeScene(SCENE::PLAY);
			return true;
		}
		// �f�o�b�N�p(���U���g�V�[���ֈړ�)
		else if (InputManager::GetInstance().GetKeyTracker().pressed.R)
		{
			m_changeScene->ChangeScene(SCENE::RESULT);
			return true;
		}
	}
	// IP���̓t���O�������Ă���Ȃ�
	else
	{
		// ���͂��ꂽ����
		char buf = m_input->Input();
		// ���͂���Ă�����
		if (buf != NULL)
		{
			IpEdit(buf);
		}
		
		// ���͊���
		if (InputManager::GetInstance().GetKeyTracker().pressed.Enter)
		{

			// m_ip�̒��g����ɂ���
			m_ip.clear();
			// m_testIP�̒��g��string�^�ɕϊ���m_ip�Ɋi�[
			for (u_int i = 0; i < m_testIp.size(); i++)
			{
				m_ip += std::string::value_type(m_testIp[i]);
			}
			// �����ɃA�N�Z�X
			if (m_ip == "0000")
			{
				std::string str = "127.0.0.1";
				NetworkClient::GetInstance().IP(str);
				m_changeScene->ChangeScene(SCENE::LOGIN);

				return true;
			}
			// ���̑��̋@��ɃA�N�Z�X
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
/// �`�揈��
/// </summary>
void TitleScene::Draw()
{
	// �^�C�g�����w�i�̕`��
	if (m_effect != nullptr)
	{
		m_effect->Render(SCENE::TITLE);
	}
	// ���̓{�b�N�X�╶���̕`��
	if (m_inputIpFlag)
	{
		DrawManager::GetInstance().Draw(*m_inputBox);

		// ������
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
/// �^�C�g���̏I������
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
/// IP�A�h���X�̏�������
/// </summary>
void TitleScene::IpEdit(char _buf)
{
	// BackSpace�������ꂽ��
	if (_buf == 'b')
	{
		if (m_testIp.size() != 0)
		{
			// 1��������
			m_testIp.pop_back();
			m_IpNum.pop_back();
		}
	}
	// delete�������ꂽ��
	else if (_buf == 'd')
	{
		m_testIp.clear();
		m_IpNum.clear();
	}
	else if (_buf == 'e')
	{

	}
	// ����ȊO�Ȃ�
	else
	{
		// ����������
		m_testIp.push_back(_buf);
		m_IpNum.push_back(_buf);
	}

}

