#pragma once
// ���� -------------------------------
#include <vector>
//-------------------------------------
// �p���� -----------------------------
#include "../GameObject.h"
// ------------------------------------
// �e ---------------------------------
#include "Bullet.h"
// ------------------------------------
// ���̑� -----------------------------
#include "../../Data.h"
// ------------------------------------

class OtherPlayer : public GameObject
{
private: // �萔

	static const int PLAYER_SIZE_X = 32;
	static const int PLAYER_SIZE_Y = 32;

public:
	// �R���X�g���N�^
	OtherPlayer(); 
	OtherPlayer(PlayerData _playerData);

	// �f�X�g���N�^
	~OtherPlayer();

	// �f�[�^�̍X�V
	void Recv(float _x, float _y,float _angle);
	void RecvBullet(float _x, float _y, bool _is, int _index);

	// �J�n
	void Start();

	// �X�V
	void Update();
	void Update(PlayerData _playerData);

	// �`��
	void TextureUpdate(DirectX::SimpleMath::Vector2 _pos);
	void Draw();
	void DrawBegin();
	void DrawEnd();


	// �\�P�b�g�̃Q�b�^�[
	SOCKET GetSocket() { return m_socket; }
	Bullet* GetBullet(int _index) { return &m_bullet[_index]; }

private:
	DirectX::SimpleMath::Vector2 MoveDirection(float _direction);

	
private:
	// �\�P�b�g
	SOCKET m_socket;

	// HP
	int m_hitPoint;

	// �v���C���[�̃|�W�V������ۊ�
	DirectX::SimpleMath::Vector2 m_playerPosition;

	// ���̃v���C���[�̒e
	Bullet m_bullet[BULLET_NUM];
	int m_number;

	SCENE m_nowScene;

	bool m_active;
};