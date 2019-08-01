#include "../pch.h"
#include "InputManager.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
System::InputManager::InputManager()
{
	mpMouse = std::make_unique<DirectX::Mouse>();
	mpKey = std::make_unique<DirectX::Keyboard>();
}

/// <summary>
/// マウスの入力状態の取得
/// </summary>
/// <returns>入力状態</returns>
DirectX::Mouse::State System::InputManager::GetMouseState()
{
	return mpMouse->GetState();
}
/// <summary>
/// キーボードの入力状態の取得
/// </summary>
/// <returns>入力状態</returns>
DirectX::Keyboard::State System::InputManager::GetKeyState()
{
	return mpKey->GetState();
}

DirectX::Keyboard::KeyboardStateTracker System::InputManager::GetKeyTracker()
{
	return mKeyTracker;
}

/// <summary>
/// Trackerの取得
/// </summary>
/// <returns>Tracker</returns>
DirectX::Mouse::ButtonStateTracker System::InputManager::GetTracker()
{
	return mTracker;
}

DirectX::Keyboard::Keys System::InputManager::GetPressedKeys()
{
	if		(GetKeyTracker().pressed.OemPeriod)	return Keyboard::Keys::OemPeriod;	// 44

	else if	(GetKeyTracker().pressed.OemComma)	return Keyboard::Keys::OemComma;	// 46

	else if (GetKeyTracker().pressed.D0)		return Keyboard::Keys::D0;			// 48
	else if	(GetKeyTracker().pressed.D1)		return Keyboard::Keys::D1;			// 49
	else if (GetKeyTracker().pressed.D2)		return Keyboard::Keys::D2;			// 50
	else if (GetKeyTracker().pressed.D3)		return Keyboard::Keys::D3;			// 51
	else if (GetKeyTracker().pressed.D4)		return Keyboard::Keys::D4;			// 52
	else if (GetKeyTracker().pressed.D5)		return Keyboard::Keys::D5;			// 53
	else if (GetKeyTracker().pressed.D6)		return Keyboard::Keys::D6;			// 54
	else if (GetKeyTracker().pressed.D7)		return Keyboard::Keys::D7;			// 55
	else if (GetKeyTracker().pressed.D8)		return Keyboard::Keys::D8;			// 56
	else if (GetKeyTracker().pressed.D9)		return Keyboard::Keys::D9;			// 57


	else if (GetKeyTracker().pressed.A)			return Keyboard::Keys::A;			// 65
	else if (GetKeyTracker().pressed.B)			return Keyboard::Keys::B;			// 66
	else if (GetKeyTracker().pressed.C)			return Keyboard::Keys::C;			// 67
	else if (GetKeyTracker().pressed.D)			return Keyboard::Keys::D;			// 68
	else if (GetKeyTracker().pressed.E)			return Keyboard::Keys::E;			// 69
	else if (GetKeyTracker().pressed.F)			return Keyboard::Keys::F;			// 70
	else if (GetKeyTracker().pressed.G)			return Keyboard::Keys::G;			// 71
	else if (GetKeyTracker().pressed.H)			return Keyboard::Keys::H;			// 72
	else if (GetKeyTracker().pressed.I)			return Keyboard::Keys::I;			// 73
	else if (GetKeyTracker().pressed.J)			return Keyboard::Keys::J;			// 74
	else if (GetKeyTracker().pressed.K)			return Keyboard::Keys::K;			// 75
	else if (GetKeyTracker().pressed.L)			return Keyboard::Keys::L;			// 76
	else if (GetKeyTracker().pressed.M)			return Keyboard::Keys::M;			// 77
	else if (GetKeyTracker().pressed.N)			return Keyboard::Keys::N;			// 78
	else if (GetKeyTracker().pressed.O)			return Keyboard::Keys::O;			// 79
	else if (GetKeyTracker().pressed.P)			return Keyboard::Keys::P;			// 80
	else if (GetKeyTracker().pressed.Q)			return Keyboard::Keys::Q;			// 81
	else if (GetKeyTracker().pressed.R)			return Keyboard::Keys::R;			// 82
	else if (GetKeyTracker().pressed.S)			return Keyboard::Keys::S;			// 83
	else if (GetKeyTracker().pressed.T)			return Keyboard::Keys::T;			// 84
	else if (GetKeyTracker().pressed.U)			return Keyboard::Keys::U;			// 85
	else if (GetKeyTracker().pressed.V)			return Keyboard::Keys::V;			// 86
	else if (GetKeyTracker().pressed.W)			return Keyboard::Keys::W;			// 87
	else if (GetKeyTracker().pressed.X)			return Keyboard::Keys::X;			// 88
	else if (GetKeyTracker().pressed.Y)			return Keyboard::Keys::Y;			// 89
	else if (GetKeyTracker().pressed.Z)			return Keyboard::Keys::Z;			// 90


	else if (GetKeyTracker().pressed.Delete)	return Keyboard::Keys::Delete;		// 46
	else if (GetKeyTracker().pressed.Back)		return Keyboard::Keys::Back;		// 08


	return DirectX::Keyboard::Keys();
}

/// <summary>
/// 更新処理
/// </summary>
void System::InputManager::Update()
{
	DirectX::Mouse::State state = GetMouseState();
	DirectX::Keyboard::State keyState = GetKeyState();
	mTracker.Update(state);
	mKeyTracker.Update(keyState);
}