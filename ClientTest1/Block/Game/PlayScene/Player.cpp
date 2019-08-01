#include "../../pch.h"
#include "Player.h"
// �V�[�� -----------------------------
#include "../ResultScene/ResultScene.h"
// ------------------------------------
// �ʐM�֌W ---------------------------
#include "../../NetworkClient.h"
// ------------------------------------
// �`��֌W ---------------------------
#include "../DrawManager.h"
// ------------------------------------
// ���̑� -----------------------------
#include "../../Debug.h"
#include "OtherPlayer.h"
#include "../../Maht.h"
#include "../InputManager.h"
// ------------------------------------

using namespace System;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �萔


const int START_POS[10][2] = { {500,0}, {404,293 },{154,475},{-154,475 },{ -404,293},{ -500,0 },{ -404,-293 },{ -154,-475 },{ 154,-475 },{ 404,-293 } };

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{

}
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_soc"></param>
/// <param name="_pos"></param>
/// <param name="_HP"></param>
/// <param name="_scene"></param>
Player::Player(SOCKET _soc,Vector2 _pos, int _HP,SCENE _scene) :
	GameObject(_pos), m_soc(_soc), m_hitPoint(_HP), m_nowScene(_scene), m_nextScene(SCENE::NON), m_changeSceneFlag(false)
{
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources/PlayScene/player.png");
	m_data.SetRect(PLAYER_SIZE_X, PLAYER_SIZE_Y);
	m_data.SetOrigin(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2);
	m_data.SetPos((float)PLAYER_POSITION_X,(float)PLAYER_POSITION_Y);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{

}

/// <summary>
/// ������
/// </summary>
void Player::Start()
{
	int tmp = m_soc % 10;

	m_position.x = (float)START_POS[tmp][0];
	m_position.y = (float)START_POS[tmp][1];

	m_direction = MoveDirection(m_angle);

	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_bullet[i].Start();
	}
}

/// <summary>
/// �v���C���[�̍X�V����
/// </summary>
void Player::Update()
{
	// �e�̔��� --------------------------------------------------------------------------------------
	if (InputManager::GetInstance().GetKeyTracker().IsKeyPressed(Keyboard::Space))
	{
		for (int i = 0; i < BULLET_NUM; i++)
		{
			if (!m_bullet[i].GetActive())
			{
				m_bullet[i].Shoot(m_position, m_direction);
				break;
			}
		}
	}
	// -----------------------------------------------------------------------------------------------
	
	// �o���b�g�̍X�V --------------------------------------------------------------------------------
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (m_bullet[i].GetActive())
		{
			m_bullet[i].Update();
		}
	}
	// -----------------------------------------------------------------------------------------------

	// ����f�[�^��ݒ�
	SetSend();

	// �摜�֌W
	m_data.SetRot(XMConvertToRadians(m_angle));
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	DrawManager::GetInstance().Draw(m_data);
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (m_bullet[i].GetActive())
		{
			m_bullet[i].Draw();
		}
	}
}

/// <summary>
/// �e�̍X�V
/// </summary>
/// <param name="_active">����</param>
/// <param name="_index">�C���f�b�N�X</param>
void Player::UpdataBullet(bool _active, int _index)
{
	m_bullet[_index].SetActive(_active);
}

// �ړ� ------------------------------------------------------------------------------------------
/// <summary>
/// �O���Ɉړ�
/// </summary>
void Player::MoveUP()
{
	m_direction = Vector2::Zero;
	m_direction = MoveDirection(m_angle);		//	�����Ă���������擾
	Vector2 dir = m_direction * (float)MOVE_SPEED;
	m_position += dir;
}
/// <summary>
/// ����Ɉړ�
/// </summary>
void Player::MoveDown()
{
	m_direction = Vector2::Zero;
	m_direction = MoveDirection(m_angle);		//	�����Ă���������擾
	Vector2 dir = m_direction * (-MOVE_SPEED);
	m_position += dir;
}

/// <summary>
/// �E�ɉ�]
/// </summary>
void Player::RotateRight()
{
	m_direction = Vector2::Zero;
	m_direction = MoveDirection(m_angle);		//	�����Ă���������擾
	m_angle += 2;
}

/// <summary>
/// ���ɉ�]
/// </summary>
void Player::RotateLeft()
{
	m_direction = Vector2::Zero;
	m_direction = MoveDirection(m_angle);		//	�����Ă���������擾
	m_angle -= 2;
}

/// <summary>
/// �f�[�^�̍X�V
/// </summary>
/// <param name="_playerData"></param>
void Player::RecvData(PlayerData _playerData)
{
	m_nowScene = _playerData.scene;
	m_nextScene = _playerData.nextScene;
	m_changeSceneFlag = _playerData.changeSceneFlag;
	
}

/// <summary>
/// ���݂̏��� m_sendData ��ݒ肷��
/// </summary>
void Player::SetSend()
{
	m_sendData.angle = m_angle;
	for (int i = 0; i < BULLET_NUM; ++i)
	{
		m_sendData.bulletPosX[i] = m_bullet[i].GetPosition().x;
		m_sendData.bulletPosY[i] = m_bullet[i].GetPosition().y;
		m_sendData.bulletActive[i] = m_bullet[i].GetActive();
	}
	m_sendData.changeSceneFlag = m_changeSceneFlag;
	m_sendData.hitPoint = m_hitPoint;
	m_sendData.posX = m_position.x;
	m_sendData.posY = m_position.y;
	m_sendData.scene = m_nowScene;
	m_sendData.nextScene = m_nextScene;
	m_sendData.socket = m_soc;
}



/// <summary>
/// �����Ă���������擾
/// </summary>
/// <param name="_direction"></param>
/// <returns></returns>
Vector2 Player::MoveDirection(float _angle)
{
	Vector2 dir = Vector2::Zero;
	float d = XMConvertToRadians(_angle);
	dir += Vector2(cosf(d), sinf(d));
	dir.Normalize();
	return dir;
}