#pragma once
// 既存 -------------------------------
#include <Keyboard.h>
// ------------------------------------
// 描画 -------------------------------
#include "../DrawManager.h"
// ------------------------------------
// シーン -----------------------------
#include "../Scene/SceneState.h"
// ------------------------------------
// マネージャー -----------------------
#include "../InputManager.h"
#include "../Effects/EffectManager.h"
// ------------------------------------
// UI ---------------------------------
#include "../UiMnager.h"
#include "../UI.h"
// ------------------------------------
// その他 -----------------------------
#include "../../Data.h"
// ------------------------------------



class LoginScene :public SceneState
{
public:
	LoginScene(ISceneChange* _changeScene);
	~LoginScene();

	// 開始処理
	void Start(System::EffectManager* _effect);

	// 更新
	bool Update(DX::StepTimer const& _timer);

	// 描画
	void Draw();

	// シーンの終了処理
	void End();

private:

	int timer;

	// エフェクト
	System::EffectManager* m_effect;

	// UI管理
	UIManeger* m_uiManager;

	// 送信データ
	char m_data[1024];

};
