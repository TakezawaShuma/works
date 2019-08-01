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
	// ������
	void Initialize(ID3D11Device1* pDevise, ID3D11DeviceContext1* pContext);

	// �f�o�C�X�̐ݒ�
	void Devise(ID3D11Device1* pDevise) { m_device = pDevise; }
	// �f�o�C�X�̎擾
	ID3D11Device1* Devise() { return m_device; }

	// �`��
	void DebugDraw(std::string _flontStr, int _num, std::string _backStr, float _x, float _y);
	void DebugDraw(std::string _str, float _x, float _y);

private:

	ID3D11Device1* m_device;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
};