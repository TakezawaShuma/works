#pragma once
#ifndef EFFECTMANAGER_DEFINE
#define EFFECTMANAGER_DEFINE

#include "../../DeviceResources.h"
#include "MyEffect.h"

#include <list>
#include <Keyboard.h>

namespace System
{
	class EffectManager
	{
	public:


		struct ConstBuffer
		{
			DirectX::SimpleMath::Matrix		matWorld;	// ワールド座標マトリクス
			DirectX::SimpleMath::Matrix		matView;	// ビューポートマトリクス
			DirectX::SimpleMath::Matrix		matProj;	// プロジェクションマトリクス
			DirectX::SimpleMath::Vector4	diffuse;	// 
			DirectX::SimpleMath::Vector4	colors;		// 色(R,G,B,A)
			DirectX::SimpleMath::Vector4	effectType;	// エフェクトの種類
			DirectX::SimpleMath::Vector4	times;		// 時間
		};
	public:
		// コンストラクタ
		EffectManager();
		// デストラクタ
		~EffectManager();

		// インプットレイアウト
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		// エフェクトマネージャーの作成
		void Create(DX::DeviceResources* _deviceResources, int _count);
		// 初期化
		void Initialize(float _life, DirectX::SimpleMath::Vector3 _pos, DirectX::SimpleMath::Vector3 _dir);
		// テクスチャの読み込み
		void LoadTexture(const wchar_t* _name);
		
		// 更新
		void Update(float _timer, int _scene, int _effectType);
		// プレイ
		void UpdatePlay(float _timer,DirectX::SimpleMath::Vector4 _actionRange, DirectX::SimpleMath::Vector2 _bgPos);
		
		// レンダリング
		void Render(int _scene);
		// 削除
		void Lost();
		
		// テクスチャを放棄する
		void LostTexture();
		
		// テクスチャの数
		int TextureListSize() { return m_textures.size(); }

		// 描画状態の設定
		void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
		
		// 描画
		void Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

		void Clear();
	private:

		// エフェクトリスト
		std::list<MyEffect*>		m_effectList;
		

		std::list<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;

		// デバイスリソース
		DX::DeviceResources*			m_deviceResources;


		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
		std::unique_ptr<DirectX::CommonStates> m_states;

		// 頂点シェーダ
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		// ピクセルシェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		// ジオメトリシェーダ
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;

		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		std::vector<DirectX::VertexPositionColorTexture>  m_vertex;

		// マトリクス群
		DirectX::SimpleMath::Matrix m_view;
		DirectX::SimpleMath::Matrix m_proj;

		std::unique_ptr<DirectX::EffectFactory> m_fxFactory;


		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_tex;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;

		// 時間
		float m_timer;

		// 円の半径
		float m_radius;
		
		// キー入力(トリガー)
		DirectX::Keyboard::KeyboardStateTracker keyTracker;

		// HLSLに渡すバッファ
		ConstBuffer m_cbuff;
	};
}
#endif // !EFFECTMANAGER_DEFINE

