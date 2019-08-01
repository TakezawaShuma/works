#pragma once

/// <summary>
/// 受信用コールバッククラス
/// </summary>
class IReception
{
public:

	virtual int Reception(char* _data) = 0;


};

/// <summary>
/// シーン切り替え用コールバッククラス
/// </summary>
class ISceneChange
{
public:
	virtual void ChangeScene(SCENE _scene) = 0;
};