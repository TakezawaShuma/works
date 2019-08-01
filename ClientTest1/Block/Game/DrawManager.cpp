#include "../pch.h"
#include <CommonStates.h>
#include "DrawManager.h"

using namespace System;

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="devise">デバイス</param>
void DrawManager::Initialize(ID3D11Device1* pDevise, ID3D11DeviceContext1* pContext)
{
	SetDevise(pDevise);

	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(pContext);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="data">描画データ構造体</param>
void DrawManager::Draw(DrawData& data)
{
	mSpriteBatch->Draw(
		(*data.GetTexture()),
		data.GetPos(),
		data.GetRectPtn(),
		data.GetColor(),
		data.GetRot(),
		data.GetOrigin(),
		data.GetScale()
	);
}

/// <summary>
/// 描画前後処理
/// </summary>
void DrawManager::Begin()
{
	DirectX::CommonStates states(mpDevice);

	mSpriteBatch->Begin(DirectX::SpriteSortMode_Deferred, states.NonPremultiplied());
}
void DrawManager::End()
{
	mSpriteBatch->End();
}

/// <summary>
/// テクスチャ読み込み
/// </summary>
/// <param name="pData">描画データ構造体</param>
/// <param name="fileName">ファイル名</param>
/// <returns>成功かどうか</returns>
bool DrawManager::LoadTexture(DrawData& data, wchar_t* pFileName)
{
	// デバイスが無いので失敗
	if (mpDevice == NULL)
	{
		return false;
	}

	DX::ThrowIfFailed
	(
		DirectX::CreateWICTextureFromFile
		(
			mpDevice,
			pFileName,
			nullptr,
			data.GetTexture()
		)
	);

	return true;
}

bool DrawManager::LoadTexture(DxTexture& pTexture, wchar_t* pFileName)
{
	// デバイスが無いので失敗
	if (mpDevice == NULL)
	{
		return false;
	}


	DX::ThrowIfFailed
	(
		DirectX::CreateWICTextureFromFile
		(
			mpDevice,
			pFileName,
			nullptr,
			&pTexture
		)
	);

	return true;
}