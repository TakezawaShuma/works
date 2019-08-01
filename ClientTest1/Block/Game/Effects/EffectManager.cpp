#include "../../pch.h"
#include "EffectManager.h"
#include "BinaryFile.h"

using namespace DX;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace System;



/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> EffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
System::EffectManager::EffectManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
System::EffectManager::~EffectManager()
{

}

/// <summary>
/// シェーダー＆デバイスの保存
/// </summary>
/// <param name="_deviceResources"></param>
/// <param name="_count"></param>
void EffectManager::Create(DeviceResources* _deviceResources,int _count)
{
	m_deviceResources = _deviceResources;
	auto device = m_deviceResources->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());
	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(m_deviceResources->GetD3DDeviceContext());

	m_states = std::make_unique<CommonStates>(device);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
	m_fxFactory = std::make_unique<EffectFactory>(device);
	m_fxFactory->SetDirectory(L"Resources");

	for (int i = 0; i < _count; i++) {
		MyEffect* effect = new MyEffect();
		m_effectList.push_back(effect);
	}

	m_radius = 0;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="_life"></param>
/// <param name="_pos"></param>
/// <param name="_dir"></param>
void EffectManager::Initialize(float _life, Vector3 _pos, Vector3 _dir)
{
	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		Vector3 vel = _dir;
		vel.Normalize();

		vel *= (float)sin(rand()) + 1.0f;
		Vector3 raff = Vector3(vel.y, -vel.x, 0);
		raff *= (float)sin(rand())*0.3f;
		vel = vel + raff;

		vel *= 0.1f;
		(*itr)->Initialize(_life, _pos, vel);
	}
	m_radius = 0;
}

/// <summary>
/// テクスチャの読み込み
/// </summary>
/// <param name="_name">テクスチャの名前</param>
void System::EffectManager::LoadTexture(const wchar_t * _name)
{
	const wchar_t* name = _name;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	DirectX::CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), name, nullptr, texture.GetAddressOf());

	m_textures.push_back(texture);
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="_times"></param>
/// <param name="_scene"></param>
/// <param name="_effectType"></param>
void EffectManager::Update(float _times,int _scene,int _effectType)
{
	_scene;
	m_timer = _times;

	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		(*itr)->Update(m_timer);
	}

	Keyboard::State key = Keyboard::Get().GetState();
	keyTracker.Update(key);


	m_cbuff.effectType.y = (float)_effectType;

}

/// <summary>
/// プレイシーンの更新処理
/// </summary>
/// <param name="_timer"></param>
/// <param name="_actionRange"></param>
/// <param name="_bgPos"></param>
void System::EffectManager::UpdatePlay(float _timer,DirectX::SimpleMath::Vector4 _actionRange, Vector2 _bgPos)
{
	Keyboard::State key = Keyboard::Get().GetState();
	keyTracker.Update(key);
	m_timer = _timer;

	// 個々のエフェクトの更新
	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		(*itr)->Update(m_timer);
	}

	// 全体の更新
	m_cbuff.diffuse = Vector4(_bgPos.x, _bgPos.y, 0, 0);
	m_cbuff.colors = _actionRange;

}

/// <summary>
/// レンダリング
/// </summary>
/// <param name="_scene"></param>
void EffectManager::Render(int _scene)
{
	m_vertex.clear();
	// 個々のエフェクトの描画
	for (auto itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		Vector3 pos = (*itr)->GetPosition();
		Vector3 vel = (*itr)->GetVelocity();

		{
			VertexPositionColorTexture vertex;
			vertex = VertexPositionColorTexture(pos, Vector4(vel.x, vel.y, vel.z, 1), Vector2(0.0f, 3.0f));
			m_vertex.push_back(vertex);
		}
	}

	// 全体エフェクトの描画
	m_cbuff.effectType.x = (float)_scene;


	Draw(Matrix::Identity, m_view, m_proj);
}

/// <summary>
/// リソースの開放
/// </summary>
void EffectManager::Lost()
{
	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		delete (*itr);
	}
	m_deviceResources = nullptr;
	LostTexture();
	m_effectList.clear();
}

/// <summary>
/// テクスチャの開放
/// </summary>
void System::EffectManager::LostTexture()
{
	m_textures.clear();
}

/// <summary>
/// レンダリング状態を設定
/// </summary>
/// <param name="camera"></param>
/// <param name="view"></param>
/// <param name="proj"></param>
void EffectManager::SetRenderState(DirectX::SimpleMath::Vector3 _camera, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj)
{
	_camera;
	m_view = _view;
	m_proj = _proj;
}

/// <summary>
/// 描画
/// </summary>
/// <param name="world"></param>
/// <param name="view"></param>
/// <param name="proj"></param>
void EffectManager::Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


	// マウス関係
	// --------------------------------------------------------------------------------------------
	Mouse::State mouse = Mouse::Get().GetState();

	RECT outputSize = m_deviceResources->GetOutputSize();
	UINT width = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT height = std::max<UINT>(outputSize.bottom - outputSize.top, 1);

	float w, h, wheel;
	w = float(mouse.x) / float(width);
	h = float(mouse.y) / float(height);
	wheel = float(mouse.scrollWheelValue) / 5000;
	// -----------------------------------------------------------------------------------------------




	//------------------------------------------------------------------------------------------------
	m_cbuff.matView = view.Transpose();
	m_cbuff.matProj = proj.Transpose();
	m_cbuff.matWorld = world.Transpose();
	m_cbuff.effectType.z = ((sinf(m_timer) + 1) / 2);
	m_cbuff.times.x = m_timer/300;

	//定数バッファの内容更新
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &m_cbuff, 0, 0);

	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// 深度バッファに参照する
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);
	// カリングは左周り
	context->RSSetState(m_states->CullNone());

	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	//context->PSSetShaderResources(0, 1, m_srv.GetAddressOf());			// モデルにテクスチャを張り付ける？
	int i = 0;
	for (auto ver = m_textures.begin(); ver != m_textures.end(); ver++, i++)
	{
		context->PSSetShaderResources(i, 1, (ver)->GetAddressOf());
	}

	

	context->IASetInputLayout(m_inputLayout.Get());

	// 半透明部分を描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertex[0], m_vertex.size());
	m_batch->End();

	// シェーダーコンテキストをNull化
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// データをクリア
/// </summary>
void System::EffectManager::Clear()
{
	m_radius = 0;
	m_timer = 0;
}

///// <summary>
///// ３Dモデルの描画
///// </summary>
//void EffectManager::RenderModel()
//{
//	// メモリーリークを起こさないように消してやる---------------------------------
//	m_tex.Reset();
//	m_rtv.Reset();
//	m_srv.Reset();
//	// ---------------------------------------------------------------------------
//
//
//	auto context = m_deviceResources->GetD3DDeviceContext();
//
//	D3D11_TEXTURE2D_DESC texDesc;
//	m_deviceResources->GetRenderTarget()->GetDesc(&texDesc);
//	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
//	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
//	m_deviceResources->GetD3DDevice()->CreateTexture2D(&texDesc, NULL, m_tex.GetAddressOf());
//
//	// レンダーターゲットビューの設定
//	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
//	memset(&rtvDesc, 0, sizeof(rtvDesc));
//	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
//	// レンダーターゲットビューの生成
//	m_deviceResources->GetD3DDevice()->CreateRenderTargetView(m_tex.Get(), &rtvDesc, &m_rtv);
//
//
//	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//	ZeroMemory(&srvDesc, sizeof(srvDesc));
//	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//	srvDesc.Texture2D.MostDetailedMip = 0;
//	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
//
//	auto hr = m_deviceResources->GetD3DDevice()->CreateShaderResourceView(
//		m_tex.Get(), &srvDesc, m_srv.GetAddressOf());
//
//	ID3D11RenderTargetView* defaultRTV = m_deviceResources->GetRenderTargetView();
//
//	ID3D11DepthStencilView* pDSV = m_deviceResources->GetDepthStencilView();
//
//	// モデルを描画するときの背景の色や透明度を設定
//	float clearColor[4] = { 1.0f, 1.0f, 1.0f,1.0f };
//	context->OMSetRenderTargets(1, m_rtv.GetAddressOf(), pDSV);
//	context->ClearRenderTargetView(m_rtv.Get(), clearColor);
//	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
//
//	context->VSSetShader(nullptr, nullptr, 0);
//	context->GSSetShader(nullptr, nullptr, 0);
//	context->PSSetShader(nullptr, nullptr, 0);
//	m_model->Draw(m_deviceResources->GetD3DDeviceContext(), *m_states, Matrix::Identity, m_view, m_proj);
//
//	clearColor[0] = 0.3f;
//	clearColor[1] = 0.3f;
//
//	context->OMSetRenderTargets(1, &defaultRTV, pDSV);
//	context->ClearRenderTargetView(defaultRTV, Colors::Aqua);			// 背景色を Aqua に固定する
//	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
//
//}
