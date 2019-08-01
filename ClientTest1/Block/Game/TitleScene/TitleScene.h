#pragma once
// 既存--------------------------------
#include <Keyboard.h>
#include <list>
#include <vector>
// ------------------------------------
// シーンインターフェース -------------
#include "../Scene/SceneState.h"
// ------------------------------------

// タスク -----------------------------
#include "../TaskBase.h"
// ------------------------------------

// 描画 -------------------------------
#include "../DrawManager.h"
// ------------------------------------


// その他 -----------------------------
#include "../../Data.h"

#include "InputIP.h"
// ------------------------------------



class Player;
class OtherPlayer;

class TitleScene :public SceneState
{
public:
	// コンストラクタ
	TitleScene(ISceneChange* _change);
	// デストラクタ
	~TitleScene();

	// 開始処理
	void Start(System::EffectManager* _effect);

	// 更新
	bool Update(DX::StepTimer const& _timer);

	// 描画
	void Draw();

	// 終了
	void End();

private:
	void IpEdit(char _buh);

private:


	// IPアドレスを格納
	std::string m_ip;
	// IPアドレスを格納する配列
	std::vector<char> m_testIp;
	// IPアドレスの数字を格納
	std::vector<int> m_IpNum;
	// 入力フラグ
	bool m_inputIpFlag;
	// 文字入力
	InputIp* m_input;

	// エフェクト
	System::EffectManager* m_effect;
	// エフェクトの種類を決定する
	int m_effectType;


	// IPアドレス入力画面画像
	System::DrawData* m_inputBox;
	// 番号画像
	System::DrawData* m_numbers;
};
