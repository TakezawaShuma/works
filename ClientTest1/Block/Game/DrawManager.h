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

	// 描画データをまとめたクラス
	struct DrawData
	{
	private:

		enum eDrawManagerFlag
		{
			NOT_TEXTURE_DELETE = (1<<0)
		};

		// フラグ
		Utility::Flag mFlag;

		// テクスチャ
		DxTexture mpTexture;

		// 座標
		DirectX::SimpleMath::Vector2 mPos;

		// 角度
		float mRot;

		// 切り取り情報
		RECT mRect;

		// カラー
		DirectX::XMVECTORF32 mColor;

		// 中心点
		DirectX::XMFLOAT2 mOrigin;

		// スケール
		DirectX::XMFLOAT2 mScale;

	public:

		// コンストラクタ
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

		// デストラクタ
		~DrawData()
		{
			if (mpTexture == NULL)		return;

			// フラグによる削除制限
			if (mFlag.Is(eDrawManagerFlag::NOT_TEXTURE_DELETE))		return;

			mpTexture->Release();
		}

	public: // getter
		// テクスチャの取得
		DxTexture* GetTexture() { return &mpTexture; }

		DirectX::SimpleMath::Vector2 GetPos() { return mPos; }

		float GetRot() { return mRot; }

		RECT GetRect() { return mRect; }
		const RECT* GetRectPtn() { return &mRect; }

		DirectX::XMVECTORF32 GetColor() { return mColor; }

		DirectX::XMFLOAT2 GetOrigin() { return mOrigin; }

		DirectX::XMFLOAT2 GetScale() { return  mScale; }

	public: // setter

		// テクスチャの設定
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

		// 初期化処理
		void Initialize(ID3D11Device1* pDevise, ID3D11DeviceContext1* pContext);

		// 描画
		void Draw(DrawData& data);

		// 描画前後処理
		void Begin();
		void End();

		// テクスチャ読み込み
		bool LoadTexture(DrawData& data, wchar_t* pFileName);
		bool LoadTexture(DxTexture& pTexture, wchar_t* pFileName);

		// テクスチャ削除
		void DeleteTexture(DrawData& pData) { pData; }

		// デバイスの設定
		void SetDevise(ID3D11Device1* pDevise)
		{
			mpDevice = pDevise;
		}

		// デバイスの取得
		ID3D11Device1* GetDevise()
		{
			return mpDevice;
		}

	private:

		ID3D11Device1* mpDevice;

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	};
}