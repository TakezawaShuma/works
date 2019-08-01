#pragma once
// 既存 -------------------------------
#include <Keyboard.h>
// ------------------------------------
// シーン -----------------------------
#include "../Scene/SceneState.h"
// ------------------------------------
// 描画関係 ---------------------------
#include "../DrawManager.h"
// ------------------------------------
// 通信関係 ---------------------------
#include "../NetworkManeger.h"
// ------------------------------------
// その他 -----------------------------
#include "../../StepTimer.h"
// ------------------------------------

class Player;

class ResultScene : public SceneState,IReception
{
public:
	ResultScene(ISceneChange* _change);
	~ResultScene();


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
	// シェーダー
	System::EffectManager* m_effect;
	
	// 貰うデータサイズ
	PlayerData m_myData;

	// 送るデータサイズ
	PlayerData m_sendData;

	// データ保管
	char m_data[1024];
	// ランクの画像
	System::DrawData* m_ranks;
};
