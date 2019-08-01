#include "../../pch.h"
// �}�l�[�W���[�֌W -------------------
#include "../InputManager.h"
#include "../NetworkManeger.h"
#include "../DrawManager.h"
// ------------------------------------

// �l�b�g���[�N�֌W -------------------
#include "../../NetworkClient.h" 
// ------------------------------------

// �V�[���֌W -------------------------
#include "LobbyScene.h"
#include "../TitleScene/TitleScene.h"
#include "../PlayScene/PlayScene.h"
// ------------------------------------

// �Q�[�����̂��̊֌W -----------------
#include "../PlayScene/Player.h"
#include "../PlayScene/OtherPlayer.h"
// ------------------------------------

using namespace std;



LobbyScene::LobbyScene(ISceneChange* _change): m_frame1(nullptr),m_frame2(nullptr),m_number(nullptr),m_ok(nullptr)
{
	m_changeScene = _change;
}

LobbyScene::~LobbyScene()
{
	End();
}

void LobbyScene::Start(System::EffectManager* _effect)
{
	_effect;
	m_sendData.socket = NetworkClient::GetInstance().GetMySocket();
	m_sendData.scene = SCENE::LOBBY;
	timeCount = 180;

	m_frame1 = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_frame1, L"Resources/LobbyLounge/Frame.png");
	m_frame1->SetRect(FRAME_SIZE_X, FRAME_SIZE_Y);
	m_frame1->SetPos(100, 8);

	m_frame2 = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_frame2, L"Resources/LobbyLounge/Frame2.png");
	m_frame2->SetRect(FRAME_SIZE_X, FRAME_SIZE_Y);
	
	m_number = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_number, L"Resources/LobbyLounge/Number.png");


	m_ok = new System::DrawData();
	System::DrawManager::GetInstance().LoadTexture(*m_ok, L"Resources/LobbyLounge/OK.png");
	m_ok->SetRect(64, 64);


	memcpy(m_data, &m_sendData, sizeof(m_data));
	NetworkClient::GetInstance().Send(m_data, sizeof(m_data));
}


bool LobbyScene::Update(DX::StepTimer const& _timer)
{

	float time = (float)_timer.GetTotalSeconds();
	time;
	PlayerData buf;
	// ��M
	NetworkManeger::GetInstance().Recv(this);



	// OK����
	// A �������Ə�����������
	if (System::InputManager::GetInstance().GetKeyTracker().IsKeyPressed(DirectX::Keyboard::Enter))
	{
		m_sendData.changeSceneFlag = 1;
		memcpy(m_data, &m_sendData, sizeof(m_data));
		NetworkClient::GetInstance().Send(m_data, sizeof(m_data));
	}
	// B �������ƃ^�C�g����
	else if (System::InputManager::GetInstance().GetKeyTracker().IsKeyPressed(DirectX::Keyboard::T))
	{
		m_sendData.changeSceneFlag = -1;
		memcpy(m_data, &m_sendData, sizeof(m_data));
		NetworkClient::GetInstance().Send(m_data, sizeof(m_data));
		m_changeScene->ChangeScene(SCENE::TITLE);
		return true;
	}


	// �V�[���؂�ւ�
	// -------------------------------------------------------------------------------------------------------------------------------------------------
	if (m_player.socket == NetworkClient::GetInstance().GetMySocket())
	{
		if (m_player.nextScene == SCENE::PLAY)
		{
			if (timeCount <= 0)
			{
				for (std::map<SOCKET, PlayerData>::iterator ite = m_otherList.begin(); ite != m_otherList.end(); ite++)
				{
					NetworkClient::GetInstance().SetOthrts(ite->first);
				}
				m_changeScene->ChangeScene(SCENE::PLAY);
				return true;
			}
			timeCount--;
		}
	}
	return true;
}

void LobbyScene::Draw()
{
	if (m_player.socket != 0)
	{
		if (m_frame1 != nullptr) System::DrawManager::GetInstance().Draw(*m_frame1);
		if (m_player.changeSceneFlag == 1)
		{
			m_ok->SetPos(500, m_frame1->GetPos().y);
			if (m_ok != nullptr) System::DrawManager::GetInstance().Draw(*m_ok);
		}
	}

	int i = 0;
	for (std::map<SOCKET, PlayerData>::iterator ite = m_otherList.begin(); ite != m_otherList.end(); ite++,i++)
	{
		int n = ite->first;
		LONG num[3];
		num[0]= n / 100;
		n = n % 100;
		num[1] = n / 10;
		num[2] = n % 10;

		if (m_frame2 != nullptr)
		{
			m_frame2->SetPos(m_frame1->GetPos().x, (m_frame1->GetPos().y + 80) + (80 * i));
			System::DrawManager::GetInstance().Draw(*m_frame2);

			for (int j = 0; j < 3; j++)
			{
				LONG h = num[j] / 5;
				LONG w = num[j] % 5;
				if (m_number != nullptr)
				{
					m_number->SetRect(NUMBER_SIZE_X * w, NUMBER_SIZE_Y * h, NUMBER_SIZE_X * (w + 1), NUMBER_SIZE_Y * (h + 1));
					m_number->SetPos((m_frame2->GetPos().x + NUMBER_SIZE_Y) + (NUMBER_SIZE_X * j), m_frame2->GetPos().y);

					System::DrawManager::GetInstance().Draw(*m_number);
				}
			}
			if (ite->second.changeSceneFlag == 1)
			{
				m_ok->SetPos(500, m_frame2->GetPos().y);
				if (m_ok != nullptr) System::DrawManager::GetInstance().Draw(*m_ok);
			}

			
		}

	}


	//int i = 0;
	//// ���̃v���C���[���ڑ����Ă�����\��
	//for (map<SOCKET, PlayerData>::iterator itr = m_otherList.begin(); itr != m_otherList.end(); itr++)
	//{
	//	std::string str = to_string(itr->first) + "     " + to_string(itr->second.changeSceneFlag) + "";
	//	Debug::GetInstance().DebugDraw(str, 300.0f, 100.0f + 20 * i);
	//	i++;
	//}

}

void LobbyScene::End()
{
	m_otherList.clear();
	m_delOtherList.clear();

	delete m_frame1;	m_frame1 = nullptr;
	delete m_frame2;	m_frame2 = nullptr;
	delete m_number;	m_number = nullptr;
	delete m_ok;		m_ok = nullptr;
}

int LobbyScene::Reception(char * _data)
{
	PlayerData p;
	memcpy(&p, _data, sizeof(PlayerData));

	if (p.socket == NetworkClient::GetInstance().GetMySocket())
	{
		m_player = p;
	}
	else
	{
		std::map<SOCKET, PlayerData>::iterator itr = m_otherList.find(p.socket);
		if (itr == m_otherList.end())
		{
			m_otherList.insert(make_pair(p.socket, p));
		}
		else
		{
			itr->second = p;
		}

		// ���O�A�E�g����
		if (p.changeSceneFlag == -1)
		{
			m_otherList.erase(p.socket);
		}
	}

	return 0;
}


void LobbyScene::ConversionSendDatas(PlayerData* _playerData)
{
	_playerData->scene = SCENE::PLAY;
}

