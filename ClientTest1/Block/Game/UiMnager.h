#pragma once

////////////////////////////////
/// UI���Ǘ����邽�߂̃N���X ///
////////////////////////////////

#include "UI.h"


class UIManeger
{
public:
	// �R���X�g���N�^
	UIManeger();
	// �f�X�g���N�^
	~UIManeger();
	// ������
	void Start(SCENE _scene);
	// �X�V
	void Update();
	// �`��
	void Render(UIType _type,int _num);
	// �I��
	void End();

private:
	// HP��UI
	UI* m_hp;

	// �i�E���[�f�B���OUI
	UI* m_connect;

	// �t���[��


};
