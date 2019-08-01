#include "Particle.hlsli"


Texture2D tex1 : register(t0);
Texture2D tex2 : register(t1);
Texture2D tex3 : register(t2);
Texture2D tex4 : register(t3);
Texture2D tex5 : register(t4);
Texture2D tex6 : register(t5);

SamplerState samLinear : register(s0);



// �m�C�Y -----------------------------------------------------------------------------------------
// �����_���m�C�Y(�e�N�X�`��)
float Random(float2 _s)
{
	// frac = �����_�ȉ������o���@12.343->0.343
	return frac(sin(dot(_s, float2(12.9898f, 78.233f)))*43758.5453f);
}
// �u���b�N�m�C�Y(�e�N�X�`��)
float BlockNoise(float2 _s)
{
	float2 p = floor(_s);
	return Random(p);
}
// �g�[���m�C�Y(�e�N�X�`��)
float ToneNoise(float2 _s)
{
	_s = float2(dot(_s, float2(127.1f, 311.7f)), dot(_s, float2(269.5f, 183.3f)));
	float ret = (float)(-1.0f + 2.0f * frac(sin(_s) * 43758.5453123f));
	return ret;
}
// �p�[�����m�C�Y(�e�N�X�`��)
float PerlinNoise(float2 _s)
{
	float2 p = floor(_s);
	float2 f = frac(_s);
	float2 u = f * f * (3.0f - 2.0f * f);

	float v00 = ToneNoise(p + float2(0, 0));
	float v10 = ToneNoise(p + float2(1, 0));
	float v01 = ToneNoise(p + float2(0, 1));
	float v11 = ToneNoise(p + float2(1, 1));


	// lerp = ���`���(2�_�Ԃ̒��Ԃ��Ƃ��Ă���)
	// dot  = ����
	return lerp(lerp(dot(v00, f - float2(0, 0)), dot(v10, f - float2(1, 0)), u.x),
		lerp(dot(v01, f - float2(0, 1)), dot(v11, f - float2(1, 1)), u.x),
		u.y) + 0.5f;
}
// FBM(�e�N�X�`��)
float FBM(float2 _s)
{
	float f = 0;
	float2 q = _s;

	f += 0.5000f * PerlinNoise(q); q = q * 2.01f;
	f += 0.2500f * PerlinNoise(q); q = q * 2.02f;
	f += 0.1250f * PerlinNoise(q); q = q * 2.03f;
	//f += 0.0625f * PerlinNoise(q); q = q * 2.01f;

	return f;
}
// ------------------------------------------------------------------------------------------------

/// <summary>
/// �O���[�X�P�[��
/// </summary>
float GrayScale(float4 _color)
{
	// �摜�̊D�F��
	float gray = _color.r * 0.2f + _color.g * 0.7f + _color.b * 0.1f;
	return gray;
}



//�@�c�݂����� ----------------------------------------------------------------------------------
/// <summary>
/// �c�܂���
/// </summary>
float Distortion(float2 _center, float _radius, float _width, float2 _tex)
{
	// ���S����̋���
	float dist = distance(_center, _tex);

	// �c�݂��o��(���Ƒ��̍����䂪�݂̑傫��)
	float distortion = 1 - smoothstep(_radius - _width, _radius, dist);

	return distortion;
}
/// <summary>
/// �c�݂ɐF��t����
/// </summary>
float4 DistortionColor(float2 _center, float _radius, float _width, float2 _tex,Texture2D _texture)
{
	// ���̘c��
	float distortion = Distortion(_center, _radius, _width, _tex);

	// �c�񂾉摜��UV���W
	float2 uv = lerp(_tex, _center, distortion);

	// �T���v�����O�摜(�c�񂾉摜 (������))
	float4 base = _texture.Sample(samLinear, uv);

	// �󂯂����̐F���(�����J�����Ƃ����⊮���Ė��߂�)
	float4 L1 = lerp(base, float4(1, 0, 0, 1), step(1, distortion));

	return L1;
}
// ------------------------------------------------------------------------------------------------

/// <summary>
/// _a �ɑ傫���l _b �ɏ������l������
/// </summary>
float2 Mod(float2 _a, float2 _b)
{
	return _a - floor(_a / _b) * _b;

}
/// <summary>
/// �f�B�]���u(input.Tex)
/// </summary>
float Dissolve(float2 _tex)
{
	float rand = PerlinNoise(_tex * 10);

	if (rand < diffuse.x)
	{
		return 0;
	}
	return 1;
}
/// <summary>
/// �u���[����(input.Tex)
/// </summary>
float4 Blur(float2 _tex,Texture2D _texture)
{
	float2 noise = float2(0.005f, 0.005f);			// float2 noise = 0.005f �ł��ł���

													// �u���[ (�C�Ⓖ�O�̃{���P)
	float4 base = _texture.Sample(samLinear, _tex + float2(noise.x, noise.y))
		+ _texture.Sample(samLinear, _tex + float2(noise.x, 0))
		+ _texture.Sample(samLinear, _tex + float2(noise.x, -noise.y))
		+ _texture.Sample(samLinear, _tex + float2(0, noise.y))
		+ _texture.Sample(samLinear, _tex + float2(0, 0))
		+ _texture.Sample(samLinear, _tex + float2(0, -noise.y))
		+ _texture.Sample(samLinear, _tex + float2(-noise.x, noise.y))
		+ _texture.Sample(samLinear, _tex + float2(-noise.x, 0))
		+ _texture.Sample(samLinear, _tex + float2(-noise.x, -noise.y));

	// �x�[�X�̖��邳�����ɖ߂�
	base /= 9;

	return base;
}

// �|�[�^�� ---------------------------------------------------------------------------------------
/// <summary>
/// �|�[�^��(input.Tex)
/// </summary>
float4 Portal(float2 _center, float _radius, float _width, float2 _tex,Texture2D _texture, Texture2D _texture2)
{
	// �c�݂��o��
	float distortion = Distortion(_center, _radius, _width, _tex);

	// �e�N�X�`���ɒ�������̍��ɂ䂪�݂����������̂𑫂�
	float2 uv = _tex + (_center - _tex) * distortion;

	float4 base = _texture.Sample(samLinear, uv);
	float4 gate = _texture2.Sample(samLinear, _tex);

	float4 L1 = lerp(base, gate, step(1, distortion));

	return L1;
}
/// <summary>
/// �|�[�^��(input.Tex, �h�炬�Ȃǂ�����Tex)
/// </summary>
float4 ShakenPortal(float2 _center, float _radius, float _width, float2 _tex, Texture2D _texture, Texture2D _texture2)
{
	// �c�݂��o��
	float distortion = Distortion(_center, _radius, _width, _tex);

	// �e�N�X�`���ɒ�������̍��ɂ䂪�݂����������̂𑫂�
	float2 uv = _tex + (_center - _tex) * distortion;


	float2 gateUV = _tex;
	float noize = PerlinNoise(gateUV * 20);

	gateUV.x += (noize - 0.5f) * 0.1f * frac(diffuse.x);
	gateUV.y += (noize - 0.5f) * 0.1f * frac(diffuse.x);


	float4 base = _texture.Sample(samLinear, uv);
	float4 gate = _texture2.Sample(samLinear, gateUV);

	float4 L1 = lerp(base, gate, step(1, distortion));

	return L1;
}
// ------------------------------------------------------------------------------------------------

/// <summary>
/// �e���r�̘g�����
/// </summary>
float4 Braunkan(float2 _uv, Texture2D _texture)
{
	float2 uv = _uv;

	// ���������߂Ă���(distans(float2(0,0),uv)�Ɠ���)
	float vignet = length(uv);

	uv /= 1 - vignet * 0.2f;

	// ���炵�����S�_��߂�
	float2 texUV = uv + float2 (0.5f, 0.5f);

	// abs() �� �A�u�\�����[�g�A��Βl���Ƃ�
	//if (texUV.x > 1 || texUV.x < 0 || texUV.y>1 || texUV.y < 0) �Ɠ���
	if (max(abs(uv.y) - 0.5f, abs(uv.x) - 0.5f) > 0)
	{
		// ������������ƃt���[����ύX�ł���
		return float4(0, 0, 0, 1);
	}

	float4 base = _texture.Sample(samLinear, texUV);
	base.a = 0;
	return base;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 i = input.Tex;
	float4 base = float4(0, 0, 0, 0);
	

	// �^�C�g���V�[��
	if (effectType.x == 0.0)
	{
		// �w�i
		base = tex1.Sample(samLinear, i);

		// �^�C�g���\��
		float4 title = tex2.Sample(samLinear, i);
		// ������\��
		if (title.a != 0)
		{
			base = title;
			base.r = (float)half3(1, effectType.z, 0);
			base.g = (float)half3(effectType.z, 0, 1);
			base.b = (float)half3(0, 1, effectType.z);
		}
		// Push to Enter
		float4 push = tex3.Sample(samLinear, i);
		// ������\��
		if (push.a != 0) { base = push; }
	}
	// ���O�C���V�[��
	else if (effectType.x == 1.0) 
	{
		// ��������
		base = float4(0, 0, 0, 1);
	}
	// ���r�[�V�[��
	else if (effectType.x == 2.0) 
	{

	}
	// �v���C�V�[��
	else if (effectType.x == 3.0) 
	{
		float4 noise;
		// �ړ����������炷
		i += diffuse.xy;
		// �w�i
		base = tex1.Sample(samLinear, i);
		float2 tex = i;
		float2 buf = tex*(times.x * 1000.0f);

		tex.x = ToneNoise(buf);
		noise = tex1.Sample(samLinear, tex);
		// ���炵�����̂�߂�
		i -= diffuse.xy;

		if (i.x <= colors.x) { base.rg = 0.7f; }
		else if (i.x >= colors.y) { base.rg = 0.7f; }
		if (i.y <= colors.z) { base.rg = 0.7f; }
		else if (i.y >= colors.w) { base.rg = 0.7f; }

		if (times.x > 0)
		{
			noise.r = times.x;
			base += noise;
		}

	}
	// ���U���g�V�[��
	else if (effectType.x == 4.0) 
	{
		base = tex1.Sample(samLinear, i);
		float4 push = tex2.Sample(samLinear, i);
		// ������\��
		if (push.a != 0) { base = push; }
	}

	return base;


	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}