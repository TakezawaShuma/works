#define TITLE	0
#define LOGIN	1
#define LOBBY	2
#define PLAY	3
#define RESULT	4

struct VS_INPUT
{
	float3 Pos : POSITION;
	float4 Color : COLOR;
	float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 Tex : TEXCOORD;
};
cbuffer ConstBuffer	: register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
	float4 diffuse;
	float4 colors;
	float4 effectType;
	float4 times;
};