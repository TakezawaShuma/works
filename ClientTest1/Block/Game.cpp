//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Debug.h"

#include "SpriteBatch.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "SimpleMath.h"
#include <CommonStates.h>

#include "Game\TaskManager.h"
#include "Game\DrawManager.h"
#include "Game\InputManager.h"
#include "Game\Effects\EffectManager.h"

#include "Game\StartScene\StartScene.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game():m_deviceResources()
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

	// ウィンドウ関係
    m_deviceResources->SetWindow(window, width, height);
    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	// DrawManager初期化
	System::DrawManager::GetInstance().Initialize(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());

	// Debugの初期化
	Debug::GetInstance().Initialize(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());




	// 自作タスクを登録
	MyGame::StartScene* pStartTask = new MyGame::StartScene(m_effectManager.get());
	Task::TaskManager::AddTask(pStartTask);

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

void Game::END()
{
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	// 入力クラスの更新
	System::InputManager::GetInstance().Update();

	// タスクマネージャの更新
	m_TaskManager.Update();

	// 追加予約されたタスクを正式に追加
	m_TaskManager.AddReserve();

	// 管理タスクがない（削除してもいいタスク）の削除
	m_TaskManager.CleanTask();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

	// タスクマネージャの描画
	m_TaskManager.Draw();

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
/// <summary>
/// ゲームがアクティブウィンドウになりつつある
/// </summary>
void Game::OnActivated()
{
    // TODO: Game is becoming active window.

}

/// <summary>
/// ゲームがバックグラウンドになりつつある
/// 非アクティブ化時
/// </summary>
void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

/// <summary>
/// ゲームが停止しているか最小化されている
/// </summary>
void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

/// <summary>
/// ゲームが再開されている
/// </summary>
void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}


/// <summary>
/// ウィンドウの移動
/// </summary>
void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

/// <summary>
/// ウィンドウサイズの変更( 横 , 縦 )
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
// プロパティ設定

/// <summary>
/// ゲームウィンドウのデフォルトサイズの設定
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 800;
}
#pragma endregion

#pragma region Direct3D Resources
// デバイスに依存するリソース

/// <summary>
/// デバイス依存のオブジェクトの初期化
/// </summary>
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	// スプライトバッチの作成
	m_SpriteBatch = std::make_unique<DirectX::SpriteBatch>(context);


	// カメラ、ビュープロジェクションの作成
	RECT outputSize = m_deviceResources->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);
	Vector3 camera = Vector3(0, 0, -5);
	Matrix view = Matrix::CreateLookAt(camera, Vector3::Zero, Vector3::UnitY);
	Matrix proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight), 0.1f, 1000.f);

	// エフェクトの作成
	m_effectManager = std::make_unique<System::EffectManager>();
	m_effectManager->Create(m_deviceResources.get(), 1);
	m_effectManager->Initialize(0, DirectX::SimpleMath::Vector3(0, 0, 0), DirectX::SimpleMath::Vector3(0, 0, 0));
	m_effectManager->SetRenderState(camera, view, proj);
}

// Allocate all memory resources that change on a window SizeChanged event.

// ウィンドウのサイズ変更イベントで変化する全てのメモリリソースを割り当てる

/// <summary>
/// ウィンドウサイズ依存のオブジェクトを初期化する
/// </summary>
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

/// <summary>
/// Direct3Dのリソースのクリーンアップ
/// </summary>
void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
	if (m_effectManager != nullptr) {
		m_effectManager->Lost();
	}
}

/// <summary>
/// デバイスの復元
/// </summary>
void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
void Game::OnClearTask()
{
	m_TaskManager.RemoveTaskAll();
	m_TaskManager.CleanTask();
}
#pragma endregion


