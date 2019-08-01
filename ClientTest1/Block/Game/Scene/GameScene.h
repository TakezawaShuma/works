#pragma once
#include <Keyboard.h>

#include "../../StepTimer.h"
#include "../TaskBase.h"
#include "../../Data.h"
#include "../Effects/EffectManager.h"

#include "../../Callback.h"


class SceneState;

class GameScene :public Task::TaskBase ,ISceneChange
{
public:
	
public:

	GameScene(System::EffectManager* _effectManager);
	~GameScene();

	// 開始処理
	void Start();

	// 更新
	bool Update();

	// 実行
	bool Execution(DX::StepTimer const& timer);

	// 描画
	void Draw();
	void DrawBegin() override;
	void DrawEnd() override;

	void ChangeScene(SCENE _nextScene);
	SceneState* CreateScene(SCENE _nextScene);


private:

	SceneState* m_activeScene;
	System::EffectManager* m_effectManager;



	DX::StepTimer m_timer;
};
