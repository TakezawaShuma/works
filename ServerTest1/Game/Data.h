#pragma once
#ifndef DATA_DEFINED
#define DATA_DEFINED

#include <WinSock2.h>

#define BULLET_NUM 25
class Data {
public:		// �萔���
	// �R�l�N�^�[�̏��
	enum SCENE
	{
		//�ڑ���
		LOGIN,
		// �^�C�g���V�[��
		TITLE,
		// ���r�[�V�[��
		LOBBY,
		// �v���C�V�[��
		PLAY,
		// ���U���g�V�[��
		RESULT,
		// ���O�A�E�g���ؒf
		LOGOUT,

		// �V�[���[��
		NON,
	};

public:		// �֐�
	// �l�b�g���[�N�̃G���[���
	static void ErrorState(int errorNumber);
private:
};

struct Player
{
	/// <summary>
	/// �R���X�g���N�^(��������Ȃ�)
	/// </summary>
	Player() :posX(0), posY(0), angle(0), hitPoint(5), socket(0), scene(Data::SCENE::NON), nextScene(Data::SCENE::NON), changeSceneFlag(0)
	{
		for (int a = 0; a < BULLET_NUM; a++)
		{
			bulletPosX[a] = 0;
			bulletPosY[a] = 0;
			bulletActive[a] = false;
		}
	}
	/// <summary>
	/// �R���X�g���N�^(�\�P�b�g���l��):posX(0), posY(0), angle(0), hitPoint(5), socket(_soc), scene(SCENE::LOBBY), nextScene(SCENE::NON), changeSceneFlag(0)
	/// </summary>
	/// <param name="_soc"></param>
	Player(SOCKET _soc) :posX(0), posY(0), angle(0), hitPoint(5), socket(_soc), scene(Data::SCENE::LOBBY), nextScene(Data::SCENE::NON), changeSceneFlag(0)
	{
		for (int a = 0; a < BULLET_NUM; a++)
		{
			bulletPosX[a] = 0;
			bulletPosY[a] = 0;
			bulletActive[a] = false;
		}
	}

	// �R�l�N�^�[�̃\�P�b�g
	SOCKET socket;

	// �R�l�N�^�[�̗̑�
	int hitPoint;

	// �R�l�N�^�[�̈ʒu
	float posX;
	float posY;

	// �����Ă���p�x
	float angle;

	// �e�̐����ʒu���L����
	float bulletPosX[BULLET_NUM];
	float bulletPosY[BULLET_NUM];
	bool bulletActive[BULLET_NUM];


	int rank;

	// �v���C���[�̌��݂̃V�[��(�N���C�A���g�Ő؂�ւ���)
	Data::SCENE scene;
	// �v���C���[�̎��؂�ւ���V�[��(�T�[�o�[�Ő؂�ւ���)
	Data::SCENE nextScene;
	// �V�[���̐؂�ւ�����(1 = ���̃V�[���ցE0 = �ҋ@�E-1 = �O�̃V�[����)
	int changeSceneFlag;
};

#endif // !DATA_DEFINED