#pragma once

////////////////////////////////
/// UIを管理するためのクラス ///
////////////////////////////////

#include "UI.h"


class UIManeger
{
public:
	// コンストラクタ
	UIManeger();
	// デストラクタ
	~UIManeger();
	// 初期化
	void Start(SCENE _scene);
	// 更新
	void Update();
	// 描画
	void Render(UIType _type,int _num);
	// 終了
	void End();

private:
	// HPのUI
	UI* m_hp;

	// ナウローディングUI
	UI* m_connect;

	// フレーム


};
