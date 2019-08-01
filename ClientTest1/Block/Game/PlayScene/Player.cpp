#include "../../pch.h"
#include "Player.h"
// シーン -----------------------------
#include "../ResultScene/ResultScene.h"
// ------------------------------------
// 通信関係 ---------------------------
#include "../../NetworkClient.h"
// ------------------------------------
// 描画関係 ---------------------------
#include "../DrawManager.h"
// ------------------------------------
// その他 -----------------------------
#include "../../Debug.h"
#include "OtherPlayer.h"
#include "../../Maht.h"
#include "../InputManager.h"
// ------------------------------------

using namespace System;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 定数


const int START_POS[10][2] = { {500,0}, {404,293 },{154,475},{-154,475 },{ -404,293},{ -500,0 },{ -404,-293 },{ -154,-475 },{ 154,-475 },{ 404,-293 } };

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{

}
/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
Player::~Player()
{

}

/// <summary>
/// 初期化
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
/// プレイヤーの更新処理
/// </summary>
void Player::Update()
{
	// 弾の発射 --------------------------------------------------------------------------------------
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
	
	// バレットの更新 --------------------------------------------------------------------------------
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (m_bullet[i].GetActive())
		{
			m_bullet[i].Update();
		}
	}
	// -----------------------------------------------------------------------------------------------

	// 送るデータを設定
	SetSend();

	// 画像関係
	m_data.SetRot(XMConvertToRadians(m_angle));
}

/// <summary>
/// 描画
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
/// 弾の更新
/// </summary>
/// <param name="_active">生存</param>
/// <param name="_index">インデックス</param>
void Player::UpdataBullet(bool _active, int _index)
{
	m_bullet[_index].SetActive(_active);
}

// 移動 ------------------------------------------------------------------------------------------
/// <summary>
/// 前方に移動
/// </summary>
void Player::MoveUP()
{
	m_direction = Vector2::Zero;
	m_direction = MoveDirection(m_angle);		//	向いている方向を取得
	Vector2 dir = m_direction * (float)MOVE_SPEED;
	m_position += dir;
}
/// <summary>
/// 後方に移動
/// </summary>
void Player::MoveDown()
{
	m_direction = Vector2::Zero;
	m_direction = MoveDirection(m_angle);		//	向いている方向を取得
	Vector2 dir = m_direction * (-MOVE_SPEED);
	m_position += dir;
}

/// <summary>
/// 右に回転
/// </summary>
void Player::RotateRight()
{
	m_direction = Vector2::Zero;
	m_direction = MoveDirection(m_angle);		//	向いている方向を取得
	m_angle += 2;
}

/// <summary>
/// 左に回転
/// </summary>
void Player::RotateLeft()
{
	m_direction = Vector2::Zero;
	m_direction = MoveDirection(m_angle);		//	向いている方向を取得
	m_angle -= 2;
}

/// <summary>
/// データの更新
/// </summary>
/// <param name="_playerData"></param>
void Player::RecvData(PlayerData _playerData)
{
	m_nowScene = _playerData.scene;
	m_nextScene = _playerData.nextScene;
	m_changeSceneFlag = _playerData.changeSceneFlag;
	
}

/// <summary>
/// 現在の情報を m_sendData を設定する
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
/// 向いている方向を取得
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