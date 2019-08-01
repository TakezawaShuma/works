#include "pch.h"
#include "Window.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Window::Window()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Window::~Window()
{
	m_deviceResources = nullptr;
}

void Window::Initialize(HWND _window, int _width, int _height, DX::DeviceResources* _device)
{
	m_deviceResources = _device;
	m_deviceResources->SetWindow(_window, _width, _height);
}

void Window::Lost()
{
	m_deviceResources = nullptr;
}

/// <summary>
/// �Q�[�����A�N�e�B�u�E�B���h�E�ɂȂ��Ă���
/// Game is becoming active window
/// </summary>
void Window::OnActivated()
{

}

/// <summary>
/// �Q�[�����w�i�E�B���h�E�ɂȂ��Ă��܂�
/// Game is becoming background window.
/// </summary>
void Window::OnDeactivated()
{
}

/// <summary>
/// �Q�[������~���Ă���(�܂��́A�ŏ�������Ă��܂�)
///  Game is being power-suspended (or minimized)
/// </summary>
void Window::OnSuspending()
{

}

/// <summary>
/// �Q�[�����ĊJ���ꂽ�i�ŏ�������߂�܂����j
/// Game is being power-resumed (or returning from minimize)
/// </summary>
void Window::OnResuming()
{
	// �X�e�b�v�^�C�}�[�̃��Z�b�g
	//m_timer.ResetElapsedTime();

}

void Window::OnWindowMoved()
{
	//auto r = m_deviceResources->GetOutputSize();
	//m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

/// <summary>
/// �Q�[���E�B���h�E�̃T�C�Y�ύX
///  Game window is being resized.
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Window::OnWindowSizeChanged(int _width, int _height)
{
	if (!m_deviceResources->WindowSizeChanged(_width, _height))
		return;

	//CreateWindowSizeDependentResources();

}

/// <summary>
/// �E�B���h�E�̃f�t�H���g�T�C�Y�̐ݒ�i�ŏ��T�C�Y��320X200�j
/// Change to desired default window size (note minimum size is 320x200)
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Window::GetDefaultSize(int & width, int & height) const
{
	width = 800;
	height = 800;
}


/// <summary>
/// �E�B���h�E�T�C�Y�ˑ��̃I�u�W�F�N�g�̏�����
/// Initialize windows-size dependent objects here
/// </summary>
void Window::CreateWindowSizeDependentResources()
{ 
	// TODO: Initialize windows-size dependent objects here.
}
