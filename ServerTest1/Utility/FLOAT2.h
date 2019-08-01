#pragma once

struct FLOAT2
{
	FLOAT2() {}
	FLOAT2(float _x, float _y) { x = _x; y = _y; }

	float x;
	float y;
};

struct FLOAT3
{
	FLOAT3() {}
	FLOAT3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

	float x;
	float y;
	float z;
};
struct FLOAT4
{
	FLOAT4() {}
	FLOAT4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }

	float x;
	float y;
	float z;
	float w;
};
