// �v���R���p�C���σw�b�_ -------------
#include "../../pch.h"
// ------------------------------------
#include "UiMnager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UIManeger::UIManeger():m_hp(nullptr),m_connect(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UIManeger::~UIManeger()
{
}

/// <summary>
/// ������
/// </summary>
void UIManeger::Start(SCENE _scene)
{
	switch (_scene)
	{
	case TITLE:
		break;
	case LOGIN:
		m_connect = new UI();
		if (m_connect != nullptr)m_connect->StartUI(UIType::NowConnection);
		break;
	case LOBBY:

		break;
	case PLAY:
		m_hp = new UI();
		if (m_hp != nullptr)m_hp->StartUI(UIType::HP);
		break;
	case RESULT:
		break;
	case LOGOUT:
		break;
	case NON:
		break;
	default:
		break;
	}
}

/// <summary>
/// UI�S�̂̍X�V�Ǘ�
/// </summary>
void UIManeger::Update()
{
	if (m_hp != nullptr)m_hp->Update();
	if (m_connect != nullptr)m_connect->Update();
}

/// <summary>
/// UI�S�̂̕`��Ǘ�
/// </summary>
/// <param name="_num"></param>
void UIManeger::Render(UIType _type, int _num)
{
	if (m_connect != nullptr)m_connect->DrawUI(_type, _num);
	if (m_hp != nullptr)m_hp->DrawUI(_type, _num);
}

/// <summary>
/// UI�̏I��
/// </summary>
void UIManeger::End()
{
	if (m_hp != nullptr)
	{
		m_hp->End();
		delete m_hp;
		m_hp = nullptr;
	}
	if (m_connect != nullptr)
	{
		m_connect->End();
		delete m_connect;
		m_connect = nullptr;
	}
}
