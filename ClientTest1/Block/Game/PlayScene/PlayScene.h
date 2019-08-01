#pragma once
#ifndef PLAYSECEN_DEFINED
#define PLAYSECEN_DEFINED

// ----------------- 既存の機能　----------------- //
// Windowsの機能
#include <locale.h>
#include <Keyboard.h>
#include <list>
#include <map>
// ---------------------------------------------- //

// ----------------- 自作ヘッダ ----------------- //
#include "../DrawManager.h"
#include "../../StepTimer.h"
#include "../Utility/Collision.h"
#include "../../Data.h"
#include "../Scene/SceneState.h"

#include "../Effects/EffectManager.h"
#include "../UiMnager.h"
#include "../UI.h"
#include "../../Callback.h"
// ---------------------------------------------- //

#define WIDTH 600
#define HEIGHT 800

#define MAX_MARGINAL_TIME 300

class Player;
class Bullet;
class OtherPlayer;

class PlayScene :public SceneState, IReception
{
public:
	// 行動範囲定数
	static const int MAX_ACTION_RANGE_W = 1000;
	static const int MIN_ACTION_RANGE_W = -1000;
	static const int MAX_ACTION_RANGE_H = 1000;
	static const int MIN_ACTION_RANGE_H = -1000;

public:
	PlayScene(ISceneChange* _change);
	~PlayScene();


	// 開始処理
	void Start(System::EffectManager* _effect);

	// 更新
	bool Update(DX::StepTimer const& _timer);

	// 描画
	void Draw();

	//シーンの終了処理
	void End();

	int Reception(char* _data)override;
	void SendPlayer();

	void DeleteExecution();
private:
	bool MovingRestrictions(DirectX::SimpleMath::Vector2 _pos);
	bool MovingRestrictions(float _posX,float _posY);

	DirectX::SimpleMath::Vector4 RestrictionEffects(DirectX::SimpleMath::Vector2 _pos);
	DirectX::SimpleMath::Vector2 MoveBackGround(DirectX::SimpleMath::Vector2 _pos);


private:

	// 自分自身
	Player* m_player;
	// プレイヤーのリスト
	std::map<SOCKET, OtherPlayer*> m_otherPlayers;

	// 送信データ格納庫
	PlayerData m_sendData;

	// 削除プレイヤーリスト
	std::list<SOCKET> m_delList;

	// 受信したデータのサイズ
	int m_size;
	// 受信データ
	char m_data[1024];

	// バックグラウンド
	DirectX::SimpleMath::Vector2 m_bgPos;

	//制限時間
	float m_marginalTime;

	// Rendering loop timer.
	float m_timer;

	// エフェクト管理
	System::EffectManager* m_effect;
	bool m_damegeEffectFlag;

	// UI管理
	UIManeger* m_uiManager;


	// エフェクト用

	// 行動範囲(X 最大値, X 最小値, Y 最大値, Y 最小値)
	DirectX::SimpleMath::Vector4 m_actionRenge;
	// バックグラウンドの移動
	DirectX::SimpleMath::Vector4 m_moveBackGround;

};
	

#endif // !PLAYSECEN_DEFINED