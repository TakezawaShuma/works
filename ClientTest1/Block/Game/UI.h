#pragma once
//////////////////////
/// UIを出すクラス ///
//////////////////////

// 継承元 -----------------------------
#include "GameObject.h"
// ------------------------------------
// 描画関係 ---------------------------
#include "DrawManager.h"
// ------------------------------------

/// <summary>
/// UIの種類
/// </summary>
enum UIType
{
	NowConnection,
	HP,
	Frame1,
	Frame2,
	MaxNum,
};


class UI :public GameObject
{
public:
	// コンストラクタ
	UI();
	// デストラクタ
	~UI();
	// 初期化
	void Start()override;
	void StartUI(UIType _type);
	// 更新
	void Update()override;
	// 描画
	void Draw()override;
	void DrawUI(UIType _type, int _num);
	// 終了
	void End();

private:
	// ヒットポイントUIの初期化
	void HpStart();
	// コネクトUIの初期化
	void ConnectStart();
	// ネームフレームの初期化
	void Frame1Start();
	void Frame2Start();
private:

};
