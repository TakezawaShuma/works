#pragma once
// ���� -------------------------------
#include <Keyboard.h>
// ------------------------------------
// �`�� -------------------------------
#include "../DrawManager.h"
// ------------------------------------
// �V�[�� -----------------------------
#include "../Scene/SceneState.h"
// ------------------------------------
// �}�l�[�W���[ -----------------------
#include "../InputManager.h"
#include "../Effects/EffectManager.h"
// ------------------------------------
// UI ---------------------------------
#include "../UiMnager.h"
#include "../UI.h"
// ------------------------------------
// ���̑� -----------------------------
#include "../../Data.h"
// ------------------------------------



class LoginScene :public SceneState
{
public:
	LoginScene(ISceneChange* _changeScene);
	~LoginScene();

	// �J�n����
	void Start(System::EffectManager* _effect);

	// �X�V
	bool Update(DX::StepTimer const& _timer);

	// �`��
	void Draw();

	// �V�[���̏I������
	void End();

private:

	int timer;

	// �G�t�F�N�g
	System::EffectManager* m_effect;

	// UI�Ǘ�
	UIManeger* m_uiManager;

	// ���M�f�[�^
	char m_data[1024];

};
