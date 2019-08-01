#include "Particle.hlsli"
static const int vnum = 4;

static const float4 offset_array[vnum] =
{
	float4(-0.5f, -0.5f, 0, 0),	// 左下
	float4(-0.5f, +0.5f, 0, 0),	// 左上
	float4(+0.5f, -0.5f, 0, 0),	// 右上
	float4(+0.5f, +0.5f, 0, 0),	// 右下

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

			// 全画面にする→ (*2) (上の offset_array を変えても可)
			element.Pos = input[0].Pos + offset_array[i] * 2;

			// テクスチャにカメラやワールド座標などを反映させる
			//element.Pos = mul(element.Pos, matWorld);
			//element.Pos = mul(element.Pos, matView);
			//element.Pos = mul(element.Pos, matProj);

			element.Color = input[0].Color;


			// カメラなどの情報を与えないと画像が反転するから直す
			element.Tex = float2 (offset_array[i].x, -offset_array[i].y) + float2(0.5f, 0.5f);
		}
		if (effectType.y == 1)
		{
			// 全画面にする→ (*2) (上の offset_array を変えても可)
			element.Pos = input[0].Pos + offset_array[i] * 2;

			// テクスチャにカメラやワールド座標などを反映させる
			element.Pos = mul(element.Pos, matWorld);
			element.Pos = mul(element.Pos, matView);
			element.Pos = mul(element.Pos, matProj);

			element.Color = input[0].Color;


			// カメラなどの情報を与えないと画像が反転するから直す
			element.Tex = -offset_array[i] + float2(0.5f, 0.5f);
		}
			output.Append(element);
	}
	output.RestartStrip();
}