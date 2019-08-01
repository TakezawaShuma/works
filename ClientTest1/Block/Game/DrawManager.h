#pragma once

#include <list>

#include "Utility\SingletonBase.h"

#include "WICTextureLoader.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"

#include "Utility\Flag.h"

namespace System
{
	typedef ID3D11ShaderResourceView* DxTexture;

	// �`��f�[�^���܂Ƃ߂��N���X
	struct DrawData
	{
	private:

		enum eDrawManagerFlag
		{
			NOT_TEXTURE_DELETE = (1<<0)
		};

		// �t���O
		Utility::Flag mFlag;

		// �e�N�X�`��
		DxTexture mpTexture;

		// ���W
		DirectX::SimpleMath::Vector2 mPos;

		// �p�x
		float mRot;

		// �؂�����
		RECT mRect;

		// �J���[
		DirectX::XMVECTORF32 mColor;

		// ���S�_
		DirectX::XMFLOAT2 mOrigin;

		// �X�P�[��
		DirectX::XMFLOAT2 mScale;

	public:

		// �R���X�g���N�^
		DrawData()
			: mpTexture(NULL)
			, mPos()
			, mRot(0.0f)
			, mRect()
			, mColor(DirectX::Colors::White)
			, mOrigin()
			, mScale(1.0f, 1.0f)
		{
		}

		// �f�X�g���N�^
		~DrawData()
		{
			if (mpTexture == NULL)		return;

			// �t���O�ɂ��폜����
			if (mFlag.Is(eDrawManagerFlag::NOT_TEXTURE_DELETE))		return;

			mpTexture->Release();
		}

	public: // getter
		// �e�N�X�`���̎擾
		DxTexture* GetTexture() { return &mpTexture; }

		DirectX::SimpleMath::Vector2 GetPos() { return mPos; }

		float GetRot() { return mRot; }

		RECT GetRect() { return mRect; }
		const RECT* GetRectPtn() { return &mRect; }

		DirectX::XMVECTORF32 GetColor() { return mColor; }

		DirectX::XMFLOAT2 GetOrigin() { return mOrigin; }

		DirectX::XMFLOAT2 GetScale() { return  mScale; }

	public: // setter

		// �e�N�X�`���̐ݒ�
		void SetTexture(DxTexture pTexture) {
			mpTexture = pTexture;
			mFlag.On(eDrawManagerFlag::NOT_TEXTURE_DELETE);
		}

		void SetPos(float x, float y) { mPos.x = x; mPos.y = y; }
		void SetPos(DirectX::SimpleMath::Vector2 pos) { mPos = pos; }

		void SetRot(float r) { mRot = r; }

		void SetRect(LONG left, LONG top, LONG right, LONG bottom) {
			mRect.left = left;
			mRect.top = top;
			mRect.right = right;
			mRect.bottom = bottom;
		}
		void SetRect(LONG right, LONG bottom) { SetRect(0, 0, right, bottom); }

		void SetColor(float r, float g, float b, float a) { mColor = { r, g, b, a }; }

		void SetOrigin(float x, float y) { mOrigin.x = x; mOrigin.y = y; }
		void SetOrigin(DirectX::SimpleMath::Vector2 origin) { mOrigin = origin; }

		void SetScale(float x, float y) { mScale.x = x; mScale.y = y; }
		void SetScale(DirectX::SimpleMath::Vector2 scale) { mScale = scale; }
	};


	class DrawManager : public Utility::SingletonBase<DrawManager>
	{

	public:

		friend class Utility::SingletonBase<DrawManager>;

	protected:

		DrawManager() {};
		~DrawManager() {};

	public:

		// ����������
		void Initialize(ID3D11Device1* pDevise, ID3D11DeviceContext1* pContext);

		// �`��
		void Draw(DrawData& data);

		// �`��O�㏈��
		void Begin();
		void End();

		// �e�N�X�`���ǂݍ���
		bool LoadTexture(DrawData& data, wchar_t* pFileName);
		bool LoadTexture(DxTexture& pTexture, wchar_t* pFileName);

		// �e�N�X�`���폜
		void DeleteTexture(DrawData& pData) { pData; }

		// �f�o�C�X�̐ݒ�
		void SetDevise(ID3D11Device1* pDevise)
		{
			mpDevice = pDevise;
		}

		// �f�o�C�X�̎擾
		ID3D11Device1* GetDevise()
		{
			return mpDevice;
		}

	private:

		ID3D11Device1* mpDevice;

		// �X�v���C�g�o�b�`
		std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	};
}