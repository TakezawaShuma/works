#pragma once
// ���� -------------------------------
#include <Mouse.h>
#include <Keyboard.h>
// ------------------------------------
// �V���O���g���� ---------------------
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
		
		// �}�E�X�̏�Ԏ擾
		DirectX::Mouse::State GetMouseState();

		// �L�[�̎擾
		DirectX::Keyboard::State GetKeyState();

		DirectX::Keyboard::KeyboardStateTracker GetKeyTracker();

		// Tracker�̎擾
		DirectX::Mouse::ButtonStateTracker GetTracker();

		// �}�E�X���W�̎擾
		int GetMousePosX()
		{
			return GetMouseState().x;
		}
		int GetMousePosY()
		{
			return GetMouseState().y;
		}

		DirectX::Keyboard::Keys GetPressedKeys();

		// �X�V
		void Update();

	private:

		// �}�E�X
		std::unique_ptr<DirectX::Mouse> mpMouse;

		// �L�[�{�[�h
		std::unique_ptr<DirectX::Keyboard> mpKey;

		// Tracker
		DirectX::Mouse::ButtonStateTracker mTracker;

		// �L�[�{�[�h�g���K�[
		DirectX::Keyboard::KeyboardStateTracker mKeyTracker;
	};
}