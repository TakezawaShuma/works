#pragma once
#include <WinSock2.h>
#include <vector>

#define MAX_DATA   5000
#define BULLET_NUM 25

enum SCENE
{
	// �^�C�g���V�[��
	TITLE,
	//�ڑ���
	LOGIN,
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


// �ʐM����v���C���[�����܂Ƃ߂��\����
struct PlayerData
{
	/// <summary>
	/// �R���X�g���N�^(��������Ȃ�)
	/// </summary>
	PlayerData() :posX(0), posY(0), angle(0), hitPoint(5), socket(0), scene(SCENE::NON), nextScene(SCENE::NON), changeSceneFlag(0)
	{
		for (int a = 0; a < BULLET_NUM; a++)
		{
			bulletPosX[a] = 0;
			bulletPosY[a] = 0;
			bulletActive[a] = false;
		}
	}
	/// <summary>
	/// �R���X�g���N�^(�\�P�b�g���l��):posX(0), posY(0), angle(0), hitPoint(5), socket(_soc), scene(SCENE::LOGIN), nextScene(SCENE::LOBBY), changeSceneFlag(true)
	/// </summary>
	/// <param name="_soc"></param>
	PlayerData(SOCKET _soc) :posX(0), posY(0), angle(0), hitPoint(5), socket(_soc), scene(SCENE::LOGIN), nextScene(SCENE::LOBBY), changeSceneFlag(0)
	{
		for (int a = 0; a < BULLET_NUM; a++)
		{
			bulletPosX[a] = 0;
			bulletPosY[a] = 0;
			bulletActive[a] = false;
		}
	}


	SOCKET socket;	// �R�l�N�^�[�̃\�P�b�g
	int hitPoint;	// �R�l�N�^�[�̗̑�
	float posX;		// �R�l�N�^�[��X�ʒu
	float posY;		// �R�l�N�^�[��Y�ʒu
	float angle;	// �����Ă���p�x

	float bulletPosX[BULLET_NUM];		// �e��X�ʒu
	float bulletPosY[BULLET_NUM];		// �e��Y�ʒu
	bool bulletActive[BULLET_NUM];		// �L����
	
	int rank;		// ����

	SCENE scene;			// �v���C���[�̌��݂̃V�[��(�N���C�A���g�Ő؂�ւ���)
	SCENE nextScene;		// �v���C���[�̎��؂�ւ���V�[��(�T�[�o�[�Ő؂�ւ���)
	// �V�[���̐؂�ւ�����
	// 
	int changeSceneFlag;
};
