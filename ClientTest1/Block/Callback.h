#pragma once

/// <summary>
/// ��M�p�R�[���o�b�N�N���X
/// </summary>
class IReception
{
public:

	virtual int Reception(char* _data) = 0;


};

/// <summary>
/// �V�[���؂�ւ��p�R�[���o�b�N�N���X
/// </summary>
class ISceneChange
{
public:
	virtual void ChangeScene(SCENE _scene) = 0;
};