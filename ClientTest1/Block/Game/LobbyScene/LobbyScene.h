#pragma once
// ���� -------------------------------
#include <map>
// ------------------------------------
// �V�[�� -----------------------------
#include "../Scene/SceneState.h"
// ------------------------------------
// �R�[���o�b�N -----------------------
#include "../../Callback.h"
// ------------------------------------
// ���̑� -----------------------------
#include "../UI.h"
#include "../UiMnager.h"
#include "../../Data.h"
// ------------------------------------
class OtherPlayer;

class LobbyScene:public SceneState, IReception
{
private:

	static const int FRAME_SIZE_X = 600;
	static const int FRAME_SIZE_Y = 64;
	static const int NUMBER_SIZE_X = 32;
	static const int NUMBER_SIZE_Y = 64;


public:
	LobbyScene(ISceneChange* _change);
	~LobbyScene();
	//static SceneState* GetInstans();
	// �J�n����
	void Start(System::EffectManager* _effect);

	// �X�V
	bool Update(DX::StepTimer const& _timer);

	// �`��
	void Draw();

	//�V�[���̏I������
	void End();

	int Reception(char* _data)override;

private:
	// �������g
	PlayerData m_player;
	// ���̃v���C���[���X�g
	std::map<SOCKET, PlayerData> m_otherList;

	// ���M�f�[�^�i�[��
	PlayerData m_sendData;

	// �폜�v���C���[���X�g
	std::vector<OtherPlayer> m_delOtherList;


	// ��M�f�[�^
	char m_data[1024];

	// Title ���� Play �ɐ؂�ւ�邽�߂̎���
	int timeCount;

	// �t���[���摜
	System::DrawData* m_frame1;
	System::DrawData* m_frame2;

	// �����摜
	System::DrawData* m_number;
	// OK�摜
	System::DrawData* m_ok;

private:
	// ���M�f�[�^�̕ϊ�
	void ConversionSendDatas(PlayerData* _playerData);

};
