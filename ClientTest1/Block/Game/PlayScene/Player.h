#pragma once
#include "PlayScene.h"
#include "../GameObject.h"
#include "../../Data.h"
#include "Bullet.h"
#include <vector>

#include <WinSock2.h>



class Player :public GameObject
{
private:
	static const int PLAYER_POSITION_X = 400;
	static const int PLAYER_POSITION_Y = 400;
	static const int MOVE_SPEED = 5;
	static const int MOVE_RANGE = 10;
	static const int PLAYER_SIZE_X = 32;
	static const int PLAYER_SIZE_Y = 32;

public:
	Player();
	Player(SOCKET _soc, DirectX::SimpleMath::Vector2 _pos, int _hp, SCENE _scene);
	~Player();

	
	void Start();	// ����������
	void Update();	// �X�V����
	void Draw();	// �`�揈��

	void UpdataBullet(bool _active,int _index);		// �e�̍X�V����

	// �v���C���[�̈ړ� //
	void MoveUP();
	void MoveDown();
	void RotateRight();
	void RotateLeft();
	//-------------------//

	// �Q�b�^�[�Z�b�^�[�Q
	// GameObject ����̂���
	DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }	// �|�W�V�������l��
	float GetAngle() { return m_angle; }								// �A���O�����l��


	// Player ���g�̂���
	float GetRadius() { return PLAYER_SIZE_X / 2; }						// ���a���擾
	Bullet* GetBullets(int _index) { return &m_bullet[_index]; }		// ���g�̒e�̏����擾
	DirectX::SimpleMath::Vector2 GetDirection() { return m_direction; }	// �����Ă���������擾


	void HP(int _hp) { m_hitPoint = _hp; }								// HP �̃Z�b�g
	int HP() { return m_hitPoint; }										// HP �̃Q�b�g

	void Damage() { m_hitPoint--; }

	PlayerData GetSend() { return m_sendData; }							// ������̊l��
	void RecvData(PlayerData _playerData);								// ��������Z�b�g


	// �v���C���[�̌��݂̏�Ԃ� sendData ��
	void SetSend();

	void UpdateData(PlayerData _data);

	//DirectX::SimpleMath::Vector2 GetTrianglePoint(int _num);



private:		// �֐�

	// Direction��Position�ɑ���
	DirectX::SimpleMath::Vector2 MoveDirection(float _direction);

private:		// �ϐ�
	SOCKET m_soc;					// �v���C���[�̃\�P�b�g
	u_int m_hitPoint;				// HP
	SCENE m_nowScene;				// ���݂̃V�[��
	SCENE m_nextScene;				// ���̃V�[��
	Bullet m_bullet[BULLET_NUM];	// �v���C���[�̒e
	int m_changeSceneFlag;			// �V�[���̐؂�ւ��t���O


	// ����v���C���[�f�[�^
	PlayerData m_sendData;
	char data[1024];
};
