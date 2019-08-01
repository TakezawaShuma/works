#include "../../pch.h"

// ----------------- 他作ヘッダ ----------------- //
// 描画関係
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "../DrawManager.h"
// ---------------------------------------------- //

// ----------------- 自作ヘッダ ----------------- //
// 入力関係
#include "../InputManager.h"
// 通信関係
#include "../../NetworkClient.h"

// ゲーム関係で必要なもの
// PlaySceneのみで必要なもの
#include "Player.h"
#include "OtherPlayer.h"
// シーン関係
#include "../NetworkManeger.h"
#include "PlayScene.h"
// デバッグ関係
#include "../../Debug.h"
// ---------------------------------------------- //

// ------------------ Using ------------------ //
using namespace std;
using namespace System;
using namespace DirectX;
using namespace DirectX::SimpleMath;
// ------------------------------------------- //

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_change"></param>
PlayScene::PlayScene(ISceneChange* _change) :
	m_player(nullptr), m_sendData(PlayerData()), m_otherPlayers(map<SOCKET, OtherPlayer*>()), m_delList(list<SOCKET>()),
	m_actionRenge((float)MAX_ACTION_RANGE_W, (float)MIN_ACTION_RANGE_W, (float)MAX_ACTION_RANGE_H, (float)MIN_ACTION_RANGE_H), m_marginalTime(0),
	m_effect(nullptr), m_damegeEffectFlag(false), m_uiManager(nullptr)
{
	m_changeScene = _change;

	//m_player = new Player(NetworkClient::GetInstance().GetMySocket(), Vector2(400, 400), 5, SCENE::PLAY);
	//m_player->Start();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
	End();
}

/// <summary>
/// スタート処理
/// </summary>
/// <param name="_effect"></param>
void PlayScene::Start(EffectManager* _effect)
{
	m_timer = 0;
	// エフェクトの獲得
	m_effect = _effect;

	// 送るデータの設定
	m_sendData.socket = NetworkClient::GetInstance().GetMySocket();
	m_sendData.scene = SCENE::PLAY;
	m_sendData.nextScene = SCENE::NON;
	m_sendData.changeSceneFlag = 0;
	// シーンが切り替わったことを報告
	memcpy(m_data, &m_sendData, sizeof(m_data));
	NetworkClient::GetInstance().Send(m_data, sizeof(m_data));



	if (m_effect != nullptr) m_effect->LoadTexture(L"Resources/PlayScene/BG.png");
	if (m_uiManager == nullptr) m_uiManager = new UIManeger();
	if (m_uiManager != nullptr)	m_uiManager->Start(SCENE::PLAY);

	//System::DrawManager::GetInstance().LoadTexture(this->mData, L"Resources/PlayScene/PlayScene.png");
	//this->mData.SetRect(320, 64);
	//this->mData.SetPos(10, 10);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="_timer"></param>
/// <param name="_state"></param>
bool PlayScene::Update(DX::StepTimer const& _timer)
{
	_timer;
	m_timer++;
	// 受信
	NetworkManeger::GetInstance().Recv(this);
	m_uiManager->Update();


	// 回線が切れた人を削除する
	DeleteExecution();

	// プレイヤーの更新
	if (m_player != nullptr)
	{
		if (m_player->HP() > 0)
		{
			// 左右回転
			if (InputManager::GetInstance().GetKeyState().Right)		m_player->RotateRight();
			else if (InputManager::GetInstance().GetKeyState().Left)	m_player->RotateLeft();
			// 前後移動
			if (InputManager::GetInstance().GetKeyState().Up)
			{
				m_player->MoveUP();
				m_bgPos += MoveBackGround(m_player->GetDirection());
			}
			else if (InputManager::GetInstance().GetKeyState().Down)
			{
				m_player->MoveDown();
				m_bgPos -= MoveBackGround(m_player->GetDirection());
			}

			// その他プレイヤーの更新
			for (map<SOCKET, OtherPlayer*>::iterator it = m_otherPlayers.begin(); it != m_otherPlayers.end(); it++)  it->second->TextureUpdate(m_player->GetPosition());

			// 自機の更新
			m_player->Update();

			// 移動範囲指定
			if (MovingRestrictions(m_player->GetPosition()))
			{
				if (m_marginalTime >= MAX_MARGINAL_TIME)
				{
					// HPを0にする
					m_player->HP(0);
				}
			}

			Vector4 damageArea = RestrictionEffects(m_player->GetPosition());
			m_effect->UpdatePlay(m_marginalTime, damageArea, m_bgPos);

			SendPlayer();
		}
		else
		{
			m_sendData = m_player->GetSend();
			m_sendData.changeSceneFlag = 1;
			m_sendData.rank = m_otherPlayers.size() + 1;
			memcpy(m_data, &m_sendData, sizeof(m_data));
			NetworkClient::GetInstance().Send(m_data, sizeof(m_data));
			m_changeScene->ChangeScene(SCENE::RESULT);
			return  true;
		}
	}

	// 他プレイヤーの人数が0以下になったらシーンを切り替える
	if (m_otherPlayers.size() <= 0 && m_timer > 180)
	{
		m_sendData.changeSceneFlag = 1;
		m_sendData.rank = 1;
		memcpy(m_data, &m_sendData, sizeof(m_data));
		NetworkClient::GetInstance().Send(m_data, sizeof(m_data));
		m_changeScene->ChangeScene(SCENE::RESULT);
		return true;
	}

	// デバック用----------------------------------------------------------------------------------
	if (InputManager::GetInstance().GetKeyTracker().IsKeyPressed(Keyboard::R))
	{
		m_sendData.changeSceneFlag = -1;
		memcpy(m_data, &m_sendData, sizeof(m_data));
		NetworkClient::GetInstance().Send(m_data, sizeof(m_data));
		m_changeScene->ChangeScene(SCENE::RESULT);
		return true;
	}
	if (InputManager::GetInstance().GetKeyTracker().IsKeyPressed(Keyboard::T))
	{
		m_sendData.changeSceneFlag = -1;
		memcpy(m_data, &m_sendData, sizeof(m_data));
		NetworkClient::GetInstance().Send(m_data, sizeof(m_data));
		m_changeScene->ChangeScene(SCENE::TITLE);
		return true;
	}
	// --------------------------------------------------------------------------------------------
	return true;
}

/// <summary>
/// 描画
/// </summary>
void PlayScene::Draw()
{
	if (m_effect != nullptr)	m_effect->Render(SCENE::PLAY);
	if (m_player != nullptr) {
		m_player->Draw();
		if (m_uiManager != nullptr)	m_uiManager->Render(UIType::HP, m_player->HP());
	}
	for (map<SOCKET,OtherPlayer*>::iterator it = m_otherPlayers.begin(); it != m_otherPlayers.end(); it++)	it->second->Draw();
}

/// <summary>
/// シーン終了時
/// </summary>
void PlayScene::End()
{
	m_effect->LostTexture();

	delete m_player; m_player = nullptr;
	m_otherPlayers.clear();
	m_delList.clear();

	if(m_uiManager)m_uiManager->End();
	delete m_uiManager;
	m_uiManager = nullptr;
}

/// <summary>
/// データの取得
/// </summary>
/// <param name="_data"></param>
/// <returns></returns>
int PlayScene::Reception(char * _data)
{
	PlayerData p;
	memcpy(&p, _data, sizeof(PlayerData));

	SOCKET soc = NetworkClient::GetInstance().GetMySocket();
	if (p.socket == soc)
	{
		if (m_player == nullptr)
		{
			// プレイヤーの獲得
			m_player = new Player(p.socket, Vector2(p.posX, p.posY), p.hitPoint, p.scene);
			m_player->SetAngle(p.angle);
			m_player->Start();
		}
		else
		{
			// バレットの状態を更新する
			for (int i = 0; i < BULLET_NUM; i++) { m_player->UpdataBullet(p.bulletActive[i], i); }
			if (m_player->HP() != p.hitPoint)
			{
				m_damegeEffectFlag = true;
				// ヒットポイントの更新
				m_player->HP(p.hitPoint);
			}
		}
	}
	else
	{
		if (NetworkClient::GetInstance().FindOthers(p.socket))
		{
			// 他プレイヤーの更新
			if (m_otherPlayers.find(p.socket) != m_otherPlayers.end())
			{
				if (p.changeSceneFlag != -1) { m_otherPlayers[p.socket]->Update(p); }
				else { m_delList.push_back(p.socket); }
			}
			// 他プレイヤーの追加
			else
			{
				if (p.socket != 0)
				{

					OtherPlayer* op = new OtherPlayer(p);
					op->Start();
					m_otherPlayers.insert(make_pair(p.socket, op));
				}
			}
		}
	}
	return 0;
}

/// <summary>
/// プレイヤーの情報を送る関数
/// </summary>
void PlayScene::SendPlayer()
{
	// 変更したプレイヤーの情報を送る
	m_sendData = m_player->GetSend();
	memcpy(m_data, &m_sendData, sizeof(m_data));
	NetworkClient::GetInstance().Send(m_data, sizeof(m_data));
}

/// <summary>
/// プレイヤーリストの削除
/// </summary>
void PlayScene::DeleteExecution()
{
	if (m_delList.size() != 0)
	{
		for each(SOCKET ver in m_delList)
		{
			m_otherPlayers.erase(ver);
		}
		m_delList.clear();
	}
}

/// <summary>
/// 範囲内にいるかの判定＆制限時間の増加
/// </summary>
/// <param name="_pos"></param>
/// <returns></returns>
bool PlayScene::MovingRestrictions(DirectX::SimpleMath::Vector2 _pos)
{
	// 範囲外に出ているか
	bool rangeFlag = false;

	if (_pos.x > m_actionRenge.x || _pos.x < m_actionRenge.y)	rangeFlag = true;
	if (_pos.y > m_actionRenge.z || _pos.y < m_actionRenge.w)	rangeFlag = true;

	if (rangeFlag) { if (m_marginalTime < MAX_MARGINAL_TIME) { m_marginalTime++; } }
	else { m_marginalTime = 0;/*if (m_marginalTime > 0) { m_marginalTime--; }*/ }
	return rangeFlag;
}

/// <summary>
/// 範囲内にいるかの判定＆制限時間の増加
/// </summary>
/// <param name="_posX"></param>
/// <param name="_posY"></param>
/// <returns></returns>
bool PlayScene::MovingRestrictions(float _posX, float _posY)
{
	// 範囲外に出ているか
	bool rangeFlag = false;

	if (_posX > m_actionRenge.x || _posX < m_actionRenge.y) { rangeFlag = true; }
	if (_posY > m_actionRenge.z || _posY < m_actionRenge.w) { rangeFlag = true; }

	if (rangeFlag) { m_marginalTime++; }
	else { m_marginalTime = 0; }

	return rangeFlag;
}

/// <summary>
/// 制限範囲のエフェクトの制御
/// </summary>
/// <param name="_pos"></param>
/// <returns></returns>
Vector4 PlayScene::RestrictionEffects(Vector2 _pos)
{
	// 制限範囲
	Vector4 ret = Vector4(0, 1, 0, 1);

	float distance;
	
	float dir;
	
	// 右限
	if (_pos.x <= 0)
	{
		distance = m_actionRenge.y - _pos.x;
		dir = 400 + distance;
		if (dir > 0)
		{
			ret.x = dir*0.00125f;
		}
	}
	// 左限
	else if (_pos.x > 0)
	{
		distance = m_actionRenge.x - _pos.x;
		dir = 400 - distance;
		if (dir > 0)
		{
			ret.y = 1 - (dir*0.00125f);
		}		
	}

	// 上限
	if (_pos.y <= 0)
	{
		distance = m_actionRenge.w - _pos.y;
		dir = 400 + distance;
		if (dir > 0)
		{
			ret.z =dir*0.00125f;
		}
	}
	// 下限
	else if (_pos.y > 0)
	{
		distance = m_actionRenge.z - _pos.y;
		dir = 400 - distance;
		if (dir > 0)
		{
			ret.w = 1 - (dir*0.00125f);
		}
	}

	return ret;
}

/// <summary>
/// バックグラウンドの移動
/// </summary>
/// <param name="_pos"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector2 PlayScene::MoveBackGround(DirectX::SimpleMath::Vector2 _pos)
{
	Vector2 ret = Vector2::Zero;

	ret = _pos *0.0065;

	return ret;
}

