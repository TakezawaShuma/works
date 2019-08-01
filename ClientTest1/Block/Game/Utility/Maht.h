#pragma once
#define MPAI 3.14159265358979323846f

// デグリー　ラジアン変換
namespace MyMaht
{
	// デグリー→ラジアン
	inline constexpr float ConvertToRadian(float degree) { return degree * (float)(MPAI / 180.0f); }
	// ラジアン→デグリー
	inline constexpr float ConvertToDegree(float radian) { return radian * (float)(180.0f / MPAI); }
}
