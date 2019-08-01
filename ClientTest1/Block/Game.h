//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "SpriteBatch.h"
#include "Window.h"

#include "Game\TaskManager.h"
#include "Game\Effects\EffectManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

	// �I������
	void END();

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

	// �^�X�N�̍폜
	void OnClearTask();


	// �E�B���h�E���b�Z�[�W
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const;

	// �f�o�C�X���\�[�X�̃|�C���^�̊l��
	DX::DeviceResources* GetDevise() { return m_deviceResources.get(); }

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

	// �f�o�C�X���\�[�X�̍쐬���ݒ�
    void CreateDeviceDependentResources();

    void CreateWindowSizeDependentResources();



private:
	std::unique_ptr<System::EffectManager>	m_effectManager;

    std::unique_ptr<DX::DeviceResources>    m_deviceResources;


	// spritebatch
	std::unique_ptr<DirectX::SpriteBatch>	m_SpriteBatch;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	// �^�X�N�}�l�[�W��
	Task::TaskManager						m_TaskManager;



};