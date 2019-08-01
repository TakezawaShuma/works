#pragma once
// 既存 -------------------------------
#include <Mouse.h>
#include <Keyboard.h>
// ------------------------------------
// シングルトン化 ---------------------
#include "Utility\SingletonBase.h"
// ------------------------------------

namespace System
{
	class InputManager : public Utility::SingletonBase<InputManager>
	{
	public:

		friend Utility::SingletonBase<InputManager>;

	private:

		InputManager();

	public:
		
		// マウスの状態取得
		DirectX::Mouse::State GetMouseState();

		// キーの取得
		DirectX::Keyboard::State GetKeyState();

		DirectX::Keyboard::KeyboardStateTracker GetKeyTracker();

		// Trackerの取得
		DirectX::Mouse::ButtonStateTracker GetTracker();

		// マウス座標の取得
		int GetMousePosX()
		{
			return GetMouseState().x;
		}
		int GetMousePosY()
		{
			return GetMouseState().y;
		}

		DirectX::Keyboard::Keys GetPressedKeys();

		// 更新
		void Update();

	private:

		// マウス
		std::unique_ptr<DirectX::Mouse> mpMouse;

		// キーボード
		std::unique_ptr<DirectX::Keyboard> mpKey;

		// Tracker
		DirectX::Mouse::ButtonStateTracker mTracker;

		// キーボードトリガー
		DirectX::Keyboard::KeyboardStateTracker mKeyTracker;
	};
}