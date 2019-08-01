#pragma once
#include "StepTimer.h"
#include "DeviceResources.h"

class Window
{
public:
	Window();
	~Window();

	void Initialize(HWND window, int width, int height, DX::DeviceResources* _device);
	void Lost();

	// ウィンドウメッセージ
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const;

private:

	void CreateWindowSizeDependentResources();

private:

	// Rendering loop timer.
	DX::StepTimer                           m_timer;
	DX::DeviceResources*					m_deviceResources;
	
};
