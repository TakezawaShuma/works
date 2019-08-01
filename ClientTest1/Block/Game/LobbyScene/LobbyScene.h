#pragma once
// 既存 -------------------------------
#include <map>
// ------------------------------------
// シーン -----------------------------
#include "../Scene/SceneState.h"
// ------------------------------------
// コールバック -----------------------
#include "../../Callback.h"
// ------------------------------------
// その他 -----------------------------
#include "../UI.h"
#include "../UiMnager.h"
#include "../../Data.h"
// ------------------------------------
class OtherPlayer;

class LobbyScene:public SceneState, IReception
{
private:

	static const int FRAME_SIZE_X = 600;
	static const int FRAME_SIZE_Y = 64;
	static const int NUMBER_SIZE_X = 32;
	static const int NUMBER_SIZE_Y = 64;


public:
	LobbyScene(ISceneChange* _change);
	~LobbyScene();
	//static SceneState* GetInstans();
	// 開始処理
	void Start(System::EffectManager* _effect);

	// 更新
	bool Update(DX::StepTimer const& _timer);

	// 描画
	void Draw();

	//シーンの終了処理
	void End();

	int Reception(char* _data)override;

private:
	// 自分自身
	PlayerData m_player;
	// 他のプレイヤーリスト
	std::map<SOCKET, PlayerData> m_otherList;

	// 送信データ格納庫
	PlayerData m_sendData;

	// 削除プレイヤーリスト
	std::vector<OtherPlayer> m_delOtherList;


	// 受信データ
	char m_data[1024];

	// Title から Play に切り替わるための時間
	int timeCount;

	// フレーム画像
	System::DrawData* m_frame1;
	System::DrawData* m_frame2;

	// 数字画像
	System::DrawData* m_number;
	// OK画像
	System::DrawData* m_ok;

private:
	// 送信データの変換
	void ConversionSendDatas(PlayerData* _playerData);

};
