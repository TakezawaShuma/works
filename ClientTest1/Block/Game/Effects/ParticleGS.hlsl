#include "Particle.hlsli"
static const int vnum = 4;

static const float4 offset_array[vnum] =
{
	float4(-0.5f, -0.5f, 0, 0),	// ����
	float4(-0.5f, +0.5f, 0, 0),	// ����
	float4(+0.5f, -0.5f, 0, 0),	// �E��
	float4(+0.5f, +0.5f, 0, 0),	// �E��

};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream< PS_INPUT > output)
{
	for (uint i = 0; i < 4; i++)
	{
			PS_INPUT element = (PS_INPUT)0;
		if (effectType.y == 0)
		{

			// �S��ʂɂ��遨 (*2) (��� offset_array ��ς��Ă���)
			element.Pos = input[0].Pos + offset_array[i] * 2;

			// �e�N�X�`���ɃJ�����⃏�[���h���W�Ȃǂ𔽉f������
			//element.Pos = mul(element.Pos, matWorld);
			//element.Pos = mul(element.Pos, matView);
			//element.Pos = mul(element.Pos, matProj);

			element.Color = input[0].Color;


			// �J�����Ȃǂ̏���^���Ȃ��Ɖ摜�����]���邩�璼��
			element.Tex = float2 (offset_array[i].x, -offset_array[i].y) + float2(0.5f, 0.5f);
		}
		if (effectType.y == 1)
		{
			// �S��ʂɂ��遨 (*2) (��� offset_array ��ς��Ă���)
			element.Pos = input[0].Pos + offset_array[i] * 2;

			// �e�N�X�`���ɃJ�����⃏�[���h���W�Ȃǂ𔽉f������
			element.Pos = mul(element.Pos, matWorld);
			element.Pos = mul(element.Pos, matView);
			element.Pos = mul(element.Pos, matProj);

			element.Color = input[0].Color;


			// �J�����Ȃǂ̏���^���Ȃ��Ɖ摜�����]���邩�璼��
			element.Tex = -offset_array[i] + float2(0.5f, 0.5f);
		}
			output.Append(element);
	}
	output.RestartStrip();
}