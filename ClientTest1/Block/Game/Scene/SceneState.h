#pragma once
#ifndef SCENESTATE_DEFINE
#define SCENESTATE_DEFINE
#include <Keyboard.h>
#include "../../DeviceResources.h"
#include "../Effects/EffectManager.h"
#include "../../Callback.h"
#include "../../StepTimer.h"

class SceneState
{
public:
	//enum EFFECT_TYPE
	//{
	//	FADEOUT,
	//	FADEIN,

	//};
public:

	//SceneState() {}
	virtual ~SceneState() = 0;

	virtual void Start(System::EffectManager* _effect) = 0;
	virtual bool Update(DX::StepTimer const& _timer) = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;


	//virtual void CreateEffect() = 0;
protected:
	// シーン切り替えのポインタ
	ISceneChange* m_changeScene;

	// 受信データ保管庫
	char m_data[1024];

	// チェンジシーンの関数ポインタ
	//int(*m_functionChangeScene)(SCENE _scene);

};
inline SceneState::~SceneState() {};

#endif // !SCENESTATE_DEFINE




