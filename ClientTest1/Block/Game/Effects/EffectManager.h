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
			DirectX::SimpleMath::Matrix		matWorld;	// ���[���h���W�}�g���N�X
			DirectX::SimpleMath::Matrix		matView;	// �r���[�|�[�g�}�g���N�X
			DirectX::SimpleMath::Matrix		matProj;	// �v���W�F�N�V�����}�g���N�X
			DirectX::SimpleMath::Vector4	diffuse;	// 
			DirectX::SimpleMath::Vector4	colors;		// �F(R,G,B,A)
			DirectX::SimpleMath::Vector4	effectType;	// �G�t�F�N�g�̎��
			DirectX::SimpleMath::Vector4	times;		// ����
		};
	public:
		// �R���X�g���N�^
		EffectManager();
		// �f�X�g���N�^
		~EffectManager();

		// �C���v�b�g���C�A�E�g
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		// �G�t�F�N�g�}�l�[�W���[�̍쐬
		void Create(DX::DeviceResources* _deviceResources, int _count);
		// ������
		void Initialize(float _life, DirectX::SimpleMath::Vector3 _pos, DirectX::SimpleMath::Vector3 _dir);
		// �e�N�X�`���̓ǂݍ���
		void LoadTexture(const wchar_t* _name);
		
		// �X�V
		void Update(float _timer, int _scene, int _effectType);
		// �v���C
		void UpdatePlay(float _timer,DirectX::SimpleMath::Vector4 _actionRange, DirectX::SimpleMath::Vector2 _bgPos);
		
		// �����_�����O
		void Render(int _scene);
		// �폜
		void Lost();
		
		// �e�N�X�`�����������
		void LostTexture();
		
		// �e�N�X�`���̐�
		int TextureListSize() { return m_textures.size(); }

		// �`���Ԃ̐ݒ�
		void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
		
		// �`��
		void Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

		void Clear();
	private:

		// �G�t�F�N�g���X�g
		std::list<MyEffect*>		m_effectList;
		

		std::list<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;

		// �f�o�C�X���\�[�X
		DX::DeviceResources*			m_deviceResources;


		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
		std::unique_ptr<DirectX::CommonStates> m_states;

		// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		// �s�N�Z���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		// �W�I���g���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;

		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		// ���̓��C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		std::vector<DirectX::VertexPositionColorTexture>  m_vertex;

		// �}�g���N�X�Q
		DirectX::SimpleMath::Matrix m_view;
		DirectX::SimpleMath::Matrix m_proj;

		std::unique_ptr<DirectX::EffectFactory> m_fxFactory;


		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_tex;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;

		// ����
		float m_timer;

		// �~�̔��a
		float m_radius;
		
		// �L�[����(�g���K�[)
		DirectX::Keyboard::KeyboardStateTracker keyTracker;

		// HLSL�ɓn���o�b�t�@
		ConstBuffer m_cbuff;
	};
}
#endif // !EFFECTMANAGER_DEFINE

