#pragma once
// ����--------------------------------
#include <Keyboard.h>
#include <list>
#include <vector>
// ------------------------------------
// �V�[���C���^�[�t�F�[�X -------------
#include "../Scene/SceneState.h"
// ------------------------------------

// �^�X�N -----------------------------
#include "../TaskBase.h"
// ------------------------------------

// �`�� -------------------------------
#include "../DrawManager.h"
// ------------------------------------


// ���̑� -----------------------------
#include "../../Data.h"

#include "InputIP.h"
// ------------------------------------



class Player;
class OtherPlayer;

class TitleScene :public SceneState
{
public:
	// �R���X�g���N�^
	TitleScene(ISceneChange* _change);
	// �f�X�g���N�^
	~TitleScene();

	// �J�n����
	void Start(System::EffectManager* _effect);

	// �X�V
	bool Update(DX::StepTimer const& _timer);

	// �`��
	void Draw();

	// �I��
	void End();

private:
	void IpEdit(char _buh);

private:


	// IP�A�h���X���i�[
	std::string m_ip;
	// IP�A�h���X���i�[����z��
	std::vector<char> m_testIp;
	// IP�A�h���X�̐������i�[
	std::vector<int> m_IpNum;
	// ���̓t���O
	bool m_inputIpFlag;
	// ��������
	InputIp* m_input;

	// �G�t�F�N�g
	System::EffectManager* m_effect;
	// �G�t�F�N�g�̎�ނ����肷��
	int m_effectType;


	// IP�A�h���X���͉�ʉ摜
	System::DrawData* m_inputBox;
	// �ԍ��摜
	System::DrawData* m_numbers;
};
