#pragma once
#include <xmmintrin.h>
#include "FLOAT2.h"
//#undef assert
//
//_ACRTIMP void __cdecl _wassert(_In_z_ wchar_t const* _Message, _In_z_ wchar_t const* _File, _In_   unsigned _Line);
//#define assert(expression) (void)(\(!!(expression)) || \(_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \)

#ifndef XM_PERMUTE_PS
#define XM_PERMUTE_PS( v, c ) _mm_shuffle_ps( v, v, c )
#endif // !XM_PERMUTE_PS
#ifndef _MM_SHUFFLE
#define _MM_SHUFFLE(fp3,fp2,fp1,fp0) (((fp3) << 6) | ((fp2) << 4) |((fp1) << 2) | ((fp0)))
#endif // !_MM_SHUFFLE


/*
__m128
恐らく
メモリーを
32byteを4個確保して
r0,r1,r2,r3
として保存しているのだと思われる
*/


namespace MyMath
{
	inline __m128 LoadFloat2(const FLOAT2* _v)
	{
		__m128 x = _mm_load_ss(&_v->x);
		__m128 y = _mm_load_ss(&_v->y);
		return _mm_unpacklo_ps(x, y);
	}

	inline __m128 __vectorcall Vector2Length(const __m128 _v)
	{
		// xの二乗とyの二乗を出す
		__m128 vLengthCell = _mm_mul_ps(_v, _v);
		//　マスクする
		__m128 vTemp = XM_PERMUTE_PS(vLengthCell, _MM_SHUFFLE(1, 1, 1, 1));
		// x^2+y^2
		vLengthCell = _mm_add_ss(vLengthCell, vTemp);
		vLengthCell = _mm_shuffle_ps(vLengthCell, vLengthCell, _MM_SHUFFLE(0, 0, 0, 0));
		vLengthCell = _mm_sqrt_ps(vLengthCell);
		return vLengthCell;
	}

	inline float __vectorcall VectorGetX(const __m128 _v)
	{
		return _mm_cvtss_f32(_v);
	}

	inline __m128 __vectorcall VectorAdd(__m128 _v1, __m128 _v2)
	{
		return _mm_add_ps(_v1, _v2);
	}
	inline __m128 __vectorcall VectorSubtract(__m128 _v1, __m128 _v2)
	{
		return _mm_sub_ps(_v1, _v2);
	}
	inline __m128 __vectorcall VectorScale(__m128 _v, float _s)
	{
		__m128 vS = _mm_set_ps1(_s);
		return _mm_mul_ps(vS, _v);
	}
	inline void __vectorcall StoreFloat2(FLOAT2* _Destination, __m128 _v)
	{
		__m128 T = _mm_shuffle_ps(_v, _v, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ss(&_Destination->x, _v);
		_mm_store_ss(&_Destination->y, T);
	}
}
