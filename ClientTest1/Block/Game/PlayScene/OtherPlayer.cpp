#include "../../pch.h"
#include "OtherPlayer.h"
// その他 -----------------------------
#include "../../Debug.h"
// ------------------------------------

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
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
/// コンストラクタ
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
/// デストラクタ
/// </summary>
OtherPlayer::~OtherPlayer()
{
}

/// <summary>
/// 情報の更新
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
/// 弾の情報の更新
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
/// 初期化
/// </summary>
void OtherPlayer::Start()
{
	// 弾の初期化
	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_bullet[i].Start();
	}

}

/// <summary>
/// 更新
/// </summary>
void OtherPlayer::Update()
{

}

/// <summary>
/// その他プレイヤーの更新
/// </summary>
/// <param name="_playerData">送られてきたプレイヤーの情報</param>
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
/// 画像の位置の更新
/// </summary>
/// <param name="_playerPos"></param>
void OtherPlayer::TextureUpdate(DirectX::SimpleMath::Vector2 _playerPos)
{
	// プレイヤーとの距離を取得
	Vector2 s = _playerPos - m_position;
	// 他のプレイヤーの弾の更新
	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_bullet[i].OtherUpdate(_playerPos);
	}

	float lemgth = s.Length();
	if (lemgth < 500)
	{
		m_active = true;
	}

	// 向いている方向を決定
	m_direction = MoveDirection(m_angle);
	m_data.SetRot(XMConvertToRadians(m_angle));
	m_data.SetPos(POS_ORIGIN - s);
}

/// <summary>
/// 描画
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
/// 向きを変換
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