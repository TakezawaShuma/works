#pragma once
//////////////////////
/// UI���o���N���X ///
//////////////////////

// �p���� -----------------------------
#include "GameObject.h"
// ------------------------------------
// �`��֌W ---------------------------
#include "DrawManager.h"
// ------------------------------------

/// <summary>
/// UI�̎��
/// </summary>
enum UIType
{
	NowConnection,
	HP,
	Frame1,
	Frame2,
	MaxNum,
};


class UI :public GameObject
{
public:
	// �R���X�g���N�^
	UI();
	// �f�X�g���N�^
	~UI();
	// ������
	void Start()override;
	void StartUI(UIType _type);
	// �X�V
	void Update()override;
	// �`��
	void Draw()override;
	void DrawUI(UIType _type, int _num);
	// �I��
	void End();

private:
	// �q�b�g�|�C���gUI�̏�����
	void HpStart();
	// �R�l�N�gUI�̏�����
	void ConnectStart();
	// �l�[���t���[���̏�����
	void Frame1Start();
	void Frame2Start();
private:

};
