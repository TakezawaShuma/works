#include "pch.h"
#include "Window.h"

/// <summary>
/// コンストラクタ
/// </summary>
Window::Window()
{

}

/// <summary>
/// デストラクタ
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
/// ゲームがアクティブウィンドウになっている
/// Game is becoming active window
/// </summary>
void Window::OnActivated()
{

}

/// <summary>
/// ゲームが背景ウィンドウになっています
/// Game is becoming background window.
/// </summary>
void Window::OnDeactivated()
{
}

/// <summary>
/// ゲームが停止している(または、最小化されています)
///  Game is being power-suspended (or minimized)
/// </summary>
void Window::OnSuspending()
{

}

/// <summary>
/// ゲームが再開された（最小化から戻りました）
/// Game is being power-resumed (or returning from minimize)
/// </summary>
void Window::OnResuming()
{
	// ステップタイマーのリセット
	//m_timer.ResetElapsedTime();

}

void Window::OnWindowMoved()
{
	//auto r = m_deviceResources->GetOutputSize();
	//m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

/// <summary>
/// ゲームウィンドウのサイズ変更
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
/// ウィンドウのデフォルトサイズの設定（最小サイズは320X200）
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
/// ウィンドウサイズ依存のオブジェクトの初期化
/// Initialize windows-size dependent objects here
/// </summary>
void Window::CreateWindowSizeDependentResources()
{ 
	// TODO: Initialize windows-size dependent objects here.
}
