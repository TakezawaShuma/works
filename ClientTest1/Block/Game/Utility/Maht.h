#pragma once
#define MPAI 3.14159265358979323846f

// �f�O���[�@���W�A���ϊ�
namespace MyMaht
{
	// �f�O���[�����W�A��
	inline constexpr float ConvertToRadian(float degree) { return degree * (float)(MPAI / 180.0f); }
	// ���W�A�����f�O���[
	inline constexpr float ConvertToDegree(float radian) { return radian * (float)(180.0f / MPAI); }
}
