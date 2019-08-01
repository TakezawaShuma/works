#pragma once

#include "Game\Utility\SingletonBase.h"
#include <d3d11_1.h>
#include <stdio.h>
#include <string>
#include <SpriteBatch.h>
#include <SpriteFont.h>



class Debug: public Utility::SingletonBase<Debug>
{
public:

	friend class Utility::SingletonBase<Debug>;
protected:
	Debug() {};
	~Debug() {};
public:
	// 初期化
	void Initialize(ID3D11Device1* pDevise, ID3D11DeviceContext1* pContext);

	// デバイスの設定
	void Devise(ID3D11Device1* pDevise) { m_device = pDevise; }
	// デバイスの取得
	ID3D11Device1* Devise() { return m_device; }

	// 描画
	void DebugDraw(std::string _flontStr, int _num, std::string _backStr, float _x, float _y);
	void DebugDraw(std::string _str, float _x, float _y);

private:

	ID3D11Device1* m_device;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
};