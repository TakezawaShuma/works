#include "../../pch.h"
#include "OtherPlayer.h"
// ���̑� -----------------------------
#include "../../Debug.h"
// ------------------------------------

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
OtherPlayer::OtherPlayer()
{
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources/PlayScene/otherPlayer.png");
		
	m_data.SetRect(PLAYER_SIZE_X, PLAYER_SIZE_Y);
	m_data.SetOrigin(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2);
	m_direction = Vector2::Zero;
	m_position = Vector2(300, 700);
	m_data.SetPos(m_position);
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerData"></param>
OtherPlayer::OtherPlayer(PlayerData _playerData)
{
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources/PlayScene/otherPlayer.png");
	m_data.SetRect(PLAYER_SIZE_X, PLAYER_SIZE_Y);
	m_data.SetOrigin(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2);
	m_direction = Vector2::Zero;
	m_data.SetPos(m_position);

	m_position.x = _playerData.posX;
	m_position.y = _playerData.posY;
	m_angle = _playerData.angle;
	m_socket = _playerData.socket;
	m_hitPoint = _playerData.hitPoint;
	m_nowScene = _playerData.scene;

	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_bullet[i].SetPosition(_playerData.bulletPosX[i], _playerData.bulletPosY[i]);
		m_bullet[i].SetActive(_playerData.bulletActive[i]);
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OtherPlayer::~OtherPlayer()
{
}

/// <summary>
/// ���̍X�V
/// </summary>
/// <param name="_x"></param>
/// <param name="_y"></param>
/// <param name="_angle"></param>
void OtherPlayer::Recv(float _x, float _y,float _angle)
{
	m_position = Vector2(_x, _y);
	m_angle = _angle;
}

/// <summary>
/// �e�̏��̍X�V
/// </summary>
/// <param name="_x"></param>
/// <param name="_y"></param>
/// <param name="_is"></param>
/// <param name="_index"></param>
void OtherPlayer::RecvBullet(float _x, float _y, bool _is, int _index)
{
	m_bullet[_index].SetActive(_is);
	m_bullet[_index].SetPosition(_x, _y);
}

/// <summary>
/// ������
/// </summary>
void OtherPlayer::Start()
{
	// �e�̏�����
	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_bullet[i].Start();
	}

}

/// <summary>
/// �X�V
/// </summary>
void OtherPlayer::Update()
{

}

/// <summary>
/// ���̑��v���C���[�̍X�V
/// </summary>
/// <param name="_playerData">�����Ă����v���C���[�̏��</param>
void OtherPlayer::Update(PlayerData _playerData)
{
	m_position.x = _playerData.posX;
	m_position.y = _playerData.posY;
	m_angle = _playerData.angle;
	m_socket = _playerData.socket;

	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_bullet[i].SetPosition(_playerData.bulletPosX[i], _playerData.bulletPosY[i]);
		m_bullet[i].SetActive(_playerData.bulletActive[i]);
	}
}

/// <summary>
/// �摜�̈ʒu�̍X�V
/// </summary>
/// <param name="_playerPos"></param>
void OtherPlayer::TextureUpdate(DirectX::SimpleMath::Vector2 _playerPos)
{
	// �v���C���[�Ƃ̋������擾
	Vector2 s = _playerPos - m_position;
	// ���̃v���C���[�̒e�̍X�V
	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_bullet[i].OtherUpdate(_playerPos);
	}

	float lemgth = s.Length();
	if (lemgth < 500)
	{
		m_active = true;
	}

	// �����Ă������������
	m_direction = MoveDirection(m_angle);
	m_data.SetRot(XMConvertToRadians(m_angle));
	m_data.SetPos(POS_ORIGIN - s);
}

/// <summary>
/// �`��
/// </summary>
void OtherPlayer::Draw()
{
	if (m_active)
	{
		System::DrawManager::GetInstance().Draw(m_data);
		for (int i = 0; i < BULLET_NUM; i++)
		{
			if (m_bullet[i].GetActive())
			{
				m_bullet[i].Draw();
			}
		}
	}
}

void OtherPlayer::DrawBegin()
{
}

void OtherPlayer::DrawEnd()
{
}

/// <summary>
/// ������ϊ�
/// </summary>
/// <param name="_direction"></param>
/// <returns></returns>
Vector2 OtherPlayer::MoveDirection(float _direction)
{
	Vector2 dir = Vector2::Zero;

	float d = XMConvertToRadians(_direction);

	dir += Vector2(cosf(d), sinf(d));
	return dir;

}