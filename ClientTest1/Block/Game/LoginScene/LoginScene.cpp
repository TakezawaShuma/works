#include "../../pch.h"
// �V�[�� -----------------------------
#include "LoginScene.h"
#include "../TitleScene/TitleScene.h"
#include "../LobbyScene/LobbyScene.h"
// ------------------------------------
// �ʐM�֌W ---------------------------
#include "../../NetworkClient.h"
#include "../NetworkManeger.h"
// ------------------------------------
// ���̑� -----------------------------
//#include "../PlayScene/Player.h"
// ------------------------------------

using namespace System;

/// <summary>
///	�R���X�g���N�^
/// </summary>
/// <param name="_changeScene"></param>
LoginScene::LoginScene(ISceneChange * _changeScene):m_uiManager(nullptr),m_effect(nullptr)
{
	m_changeScene = _changeScene;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LoginScene::~LoginScene()
{
	End();
}

/// <summary>
/// ������
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
/// �X�V
/// </summary>
/// <param name="_timer"></param>
/// <returns></returns>
bool LoginScene::Update(DX::StepTimer const& _timer)
{
	float time = (float)_timer.GetTotalSeconds();
	time;

	// ���O�C���������ǂ����̏��̎󂯎��
	SOCKET soc = NetworkManeger::GetInstance().Recv();

	m_effect->Update(time, SCENE::LOGIN, 0);
	if (m_uiManager != nullptr) m_uiManager->Update();


	// ���O�C�����Ă�����
	if (soc != 0)
	{
		//���g�̃\�P�b�g��o�^
		NetworkClient::GetInstance().SetMySocket(soc);
		// �o�^��V�[���؂�ւ�
		m_changeScene->ChangeScene(SCENE::LOBBY);
		return true;
	}
	else { timer++; }

	// ��莞�ԃ��O�C���ł��Ȃ�������^�C�g���֖߂�
	if (timer > 300)
	{
		m_changeScene->ChangeScene(SCENE::TITLE);
	}
	return true;
}

/// <summary>
/// �`��
/// </summary>
void LoginScene::Draw()
{
	m_effect->Render(SCENE::LOGIN);
	if (m_uiManager != nullptr)	m_uiManager->Render(UIType::NowConnection, 0);
}

/// <summary>
/// �I��
/// </summary>
void LoginScene::End()
{
	if (m_effect->TextureListSize() != 0) { m_effect->LostTexture(); }
	m_uiManager->End();
	delete m_uiManager;	m_uiManager = nullptr;
}

