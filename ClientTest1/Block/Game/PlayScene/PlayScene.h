#pragma once
#ifndef PLAYSECEN_DEFINED
#define PLAYSECEN_DEFINED

// ----------------- �����̋@�\�@----------------- //
// Windows�̋@�\
#include <locale.h>
#include <Keyboard.h>
#include <list>
#include <map>
// ---------------------------------------------- //

// ----------------- ����w�b�_ ----------------- //
#include "../DrawManager.h"
#include "../../StepTimer.h"
#include "../Utility/Collision.h"
#include "../../Data.h"
#include "../Scene/SceneState.h"

#include "../Effects/EffectManager.h"
#include "../UiMnager.h"
#include "../UI.h"
#include "../../Callback.h"
// ---------------------------------------------- //

#define WIDTH 600
#define HEIGHT 800

#define MAX_MARGINAL_TIME 300

class Player;
class Bullet;
class OtherPlayer;

class PlayScene :public SceneState, IReception
{
public:
	// �s���͈͒萔
	static const int MAX_ACTION_RANGE_W = 1000;
	static const int MIN_ACTION_RANGE_W = -1000;
	static const int MAX_ACTION_RANGE_H = 1000;
	static const int MIN_ACTION_RANGE_H = -1000;

public:
	PlayScene(ISceneChange* _change);
	~PlayScene();


	// �J�n����
	void Start(System::EffectManager* _effect);

	// �X�V
	bool Update(DX::StepTimer const& _timer);

	// �`��
	void Draw();

	//�V�[���̏I������
	void End();

	int Reception(char* _data)override;
	void SendPlayer();

	void DeleteExecution();
private:
	bool MovingRestrictions(DirectX::SimpleMath::Vector2 _pos);
	bool MovingRestrictions(float _posX,float _posY);

	DirectX::SimpleMath::Vector4 RestrictionEffects(DirectX::SimpleMath::Vector2 _pos);
	DirectX::SimpleMath::Vector2 MoveBackGround(DirectX::SimpleMath::Vector2 _pos);


private:

	// �������g
	Player* m_player;
	// �v���C���[�̃��X�g
	std::map<SOCKET, OtherPlayer*> m_otherPlayers;

	// ���M�f�[�^�i�[��
	PlayerData m_sendData;

	// �폜�v���C���[���X�g
	std::list<SOCKET> m_delList;

	// ��M�����f�[�^�̃T�C�Y
	int m_size;
	// ��M�f�[�^
	char m_data[1024];

	// �o�b�N�O���E���h
	DirectX::SimpleMath::Vector2 m_bgPos;

	//��������
	float m_marginalTime;

	// Rendering loop timer.
	float m_timer;

	// �G�t�F�N�g�Ǘ�
	System::EffectManager* m_effect;
	bool m_damegeEffectFlag;

	// UI�Ǘ�
	UIManeger* m_uiManager;


	// �G�t�F�N�g�p

	// �s���͈�(X �ő�l, X �ŏ��l, Y �ő�l, Y �ŏ��l)
	DirectX::SimpleMath::Vector4 m_actionRenge;
	// �o�b�N�O���E���h�̈ړ�
	DirectX::SimpleMath::Vector4 m_moveBackGround;

};
	

#endif // !PLAYSECEN_DEFINED