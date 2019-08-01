#pragma once

#include <math.h>
#include "FLOAT2.h"
#include "MyMath.h"


#ifndef UTILITY
#define UTILITY
using namespace MyMath;
namespace Utility
{
#define PAI 3.14159265359

		
	struct Vector2 :public FLOAT2
	{
		Vector2() :FLOAT2(0.0f, 0.0f) {}
		explicit Vector2(float _x) :FLOAT2(_x, _x) {}
		Vector2(float _x, float _y) { x = _x; y = _y; }

		Vector2& operator= (const Vector2& _v) { x = _v.x; y = _v.y; return *this; }
		Vector2& operator+= (const Vector2& _v) { x += _v.x; y += _v.y; return *this; }
		Vector2& operator-= (const Vector2& _v) { x -= _v.x; y -= _v.y; return *this; }
		Vector2& operator*= (const float& _s) { x *= _s; y *= _s; return *this; }
		Vector2& operator/= (const float& _s) { if (_s != 0) { x /= _s; y /= _s;  return *this; }return Vector2(0, 0); }

		Vector2& operator+ () { return *this; }
		Vector2& operator- () { return Vector2(-x, -y); }


		//float Length() { float d = (float)sqrt((x*x) + (y*y)); return d; }
		float Length()
		{
			__m128 v1 = LoadFloat2(this);
			__m128 X = Vector2Length(v1);
			return VectorGetX(X);
		}
	};

	inline Vector2 operator+ (const Vector2& _v1, const Vector2& _v2)
	{
		__m128 v1 = LoadFloat2(&_v1);
		__m128 v2 = LoadFloat2(&_v2);
		__m128 X = VectorAdd(v1, v2);
		Vector2 ret;
		StoreFloat2(&ret, X);
		return ret;
	}
	inline Vector2 operator- (const Vector2& _v1, const Vector2& _v2) 
	{
		__m128 v1 = LoadFloat2(&_v1);
		__m128 v2 = LoadFloat2(&_v2);
		__m128 X = VectorSubtract(v1, v2);
		Vector2 ret;
		StoreFloat2(&ret, X);
		return ret;
	}
	inline Vector2 operator* (const Vector2& _v, float _s)
	{
		__m128 v1 = LoadFloat2(&_v);
		__m128 X = VectorScale(v1, _s);
		Vector2 ret;
		StoreFloat2(&ret, X);
		return ret;
	}

	struct Vector4:public FLOAT4
	{
		Vector4() :FLOAT4(0.0f, 0.0f, 0.0f, 0.0f) {}
		explicit Vector4(float _x) :FLOAT4(_x, _x, _x, _x) {}
		Vector4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }

		Vector4& operator= (const Vector4& _v)	{ x = _v.x; y = _v.y; z = _v.z; w = _v.w; return *this; }
		Vector4& operator-= (const Vector4& _v) { x -= _v.x; y -= _v.y; z -= _v.z; w -= _v.w; return *this; }
		Vector4& operator+= (const Vector4& _v) { x += _v.x; y += _v.y; z += _v.z; w += _v.w; return *this; }
		Vector4& operator*= (const float& _s)	{ x *= _s; y *= _s;  z *= _s; w *= _s; return *this; }
		Vector4& operator/= (const float& _s)	{ if (_s != 0) { x /= _s; y /= _s;  z /= _s; w /= _s; return *this; }return Vector4(0, 0, 0, 0); }

		Vector4& operator+ () { return *this; }
		Vector4& operator- () { return Vector4(-x, -y, -z, -w); }

	};
	

	class Collistions
	{
	public:
		Collistions();
		~Collistions();
		static Collistions* GetInstans();


		// 円と線分のあたり判定
		bool HitLineAndCircle(Vector2 _lineStart/*線分の始点*/, Vector2 _lineEnd/*線分の終点*/, Vector2 _circlePos/*円の中心*/, float _radius/*半径*/)
		{
			mLineSegment = Vectol(_lineStart, _lineEnd);
			mStartToCircle = Vectol(_lineStart, _circlePos);
			mEndToCircle = Vectol(_lineEnd, _circlePos);
			mStartPointAngleR = RadianAngle(mLineSegment, mStartToCircle);
			mVerticalLine = (float)(mStartToCircle.Length() * sin(mStartPointAngleR));

			// 線分と円の中心との垂直線が半径より小さい場合
			if (mVerticalLine <= _radius)
			{
				// 例外 ->　円の中心が線分の両端より外にある場合
				// 線分とベクトルAの内角 * 線分とベクトルBの内角 がプラスの時当たってないかもしれない。
				if (InnerProduct(mStartToCircle, mLineSegment, RadianAngle(mLineSegment, mStartToCircle))
					*InnerProduct(mEndToCircle, mLineSegment, RadianAngle(mLineSegment, mEndToCircle)) > 0)
				{
					// 例外中に当たっている条件
					// ベクトルA や ベクトルB が円の半径より小さい場合は当たっている
					if (mStartToCircle.Length() < _radius || mEndToCircle.Length() < _radius) { return true; }
					return false;
				}
				return true;
			}
			return false;
		}
		bool HitLineAndCircle(float _sX,float _sY/*線分の始点*/, float _eX,float _eY/*線分の終点*/, float _circleX,float _circleY/*円の中心*/, float _radius/*半径*/)
		{
			mLineSegment = Vectol(_sX, _sY, _eX, _eY);
			mStartToCircle = Vectol(_sX, _sY, _circleX, _circleY);
			mEndToCircle = Vectol(_eX, _eY, _circleX, _circleY);
			mStartPointAngleR = RadianAngle(mLineSegment, mStartToCircle);
			mVerticalLine = (float)(mStartToCircle.Length() * sin(mStartPointAngleR));

			// 線分と円の中心との垂直線が半径より小さい場合
			if (mVerticalLine <= _radius)
			{
				// 例外 ->　円の中心が線分の両端より外にある場合
				// 線分とベクトルAの内角 * 線分とベクトルBの内角 がプラスの時当たってないかもしれない。
				if (InnerProduct(mStartToCircle, mLineSegment, RadianAngle(mLineSegment, mStartToCircle))
					*InnerProduct(mEndToCircle, mLineSegment, RadianAngle(mLineSegment, mEndToCircle)) > 0)
				{
					// 例外中に当たっている条件
					// ベクトルA や ベクトルB が円の半径より小さい場合は当たっている
					if (mStartToCircle.Length() < _radius || mEndToCircle.Length() < _radius) { return true; }
					return false;
				}
				return true;
			}
			return false;

		}
		// 円と円のあたり判定
		bool HitCircleAndCircle(Vector2 _circle1Pos, float _radius1, Vector2 _circle2Pos, float _radius2)
		{
			// 二点間の距離の二乗を算出
			float x = (_circle1Pos.x - _circle2Pos.x)*(_circle1Pos.x - _circle2Pos.x);
			float y = (_circle1Pos.y - _circle2Pos.y)*(_circle1Pos.y - _circle2Pos.y);

			// 物の半径の合計値の二乗を算出
			float r = (_radius2 + _radius1)*(_radius2 + _radius1);

			if (x + y <= r)
			{
				return true;
			}
			return false;
		}
		bool HitCircleAndCircle(float _x1, float _y1, float _radius1, float _x2, float _y2, float _radius2)
		{

			// 二点間の距離の二乗を算出
			float x = (_x1 - _x2)*(_x1 - _x2);
			float y = (_y1 - _y2)*(_y1- _y2);

			// 物の半径の合計値の二乗を算出
			float r = (_radius2 + _radius1)*(_radius2 + _radius1);

			if (x + y <= r)
			{
				return true;
			}
			return false;
		}
		// 円と点のあたり判定
		bool HitCircleAndPoint(Vector2 _point, Vector2 _circlePos, float _radius)
		{
			float x = (_point.x - _circlePos.x)*(_point.x - _circlePos.x);
			float y = (_point.y - _circlePos.y)*(_point.y - _circlePos.y);

			if (x + y <= _radius*_radius)
			{
				return true;
			}
			return false;
		}
		bool HitCircleAndPoint(float _pointX, float _pointY, float _circleX, float _circleY, float _radius)
		{
			float x = (_pointX - _circleX)*(_pointX - _circleX);
			float y = (_pointY - _circleY)*(_pointY - _circleY);

			if (x + y <= _radius*_radius)
			{
				return true;
			}
			return false;
		}
		// 三角形と点のあたり判定
		bool HitTriangleAndPoint(Vector2 _point, Vector2 _triPosA, Vector2 _triPosB, Vector2 _triPosC)
		{
			Vector2 AB = _triPosB - _triPosA;
			Vector2 BP = _point - _triPosB;

			Vector2 BC = _triPosC - _triPosB;
			Vector2 CP = _point - _triPosC;

			Vector2 CA = _triPosA - _triPosC;
			Vector2 AP = _point - _triPosA;


			double c1 = (AB.x * BP.y) - (AB.y * BP.x);
			double c2 = (BC.x * CP.y) - (BC.y * CP.x);
			double c3 = (CA.x * AP.y) - (CA.y * AP.x);

			if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) { return true; }
			else { return false; }

		}

	private:


		// 円と線分　START
		Vector2 mLineSegment;		// 線分ベクトル

		Vector2 mStartToCircle;	// 線分の始点から円の中心までのベクトル
		Vector2 mEndToCircle;		// 線分の終点から円の中心までのベクトル

		float mVerticalLine;	// 線分に対する円の中心までの垂直線

		float mStartPointAngleD;	// 始点を基準とする線分と円の中心までの角度Θ(デグリー角)
		float mEndPointAngleD;		// 終点を基準とする線分と円の中心までの角度Θ(デグリー角)

		float mStartPointAngleR;	// 始点を基準とする線分と円の中心までの角度Θ(ラジアン角)
		float mEndPointAngleR;		// 終点を基準とする線分と円の中心までの角度Θ(ラジアン角)

									// 円と線分　END

									// 円と円　START
									// 円と円　END
	private:
		// 2点を結ぶベクトル
		Vector2 Vectol(Vector2 start, Vector2 end)
		{
			Vector2 vec = end - start;
			return vec;
		}
		Vector2 Vectol(float _sX, float _sY, float _eX, float _eY)
		{
			Vector2 vec = Vector2(_sX - _eX, _sY - _eY);
			return vec;
		}

		// ベクトル同士のなす角(デグリー角出力)
		float DegreeAngle(Vector2 A, Vector2 B)
		{
			double cos;

			cos = ((A.x*B.x) + (A.y*B.y)) / (A.Length()*B.Length());
			cos = ((A.x*B.x) + (A.y*B.y)) / (A.Length()*B.Length());
			float radian = (float)acos(cos);
			float degree = (float)(radian*(180 / PAI));
			return degree;
		}
		// ベクトル同士のなす角(ラジアン角出力)
		float RadianAngle(Vector2 A, Vector2 B)
		{
			double cos;
			cos = ((A.x*B.x) + (A.y*B.y)) / (A.Length()*B.Length());
			float radian = (float)acos(cos);
			return radian;
		}

		// 二つのベクトルの内積
		float InnerProduct(Vector2 A, Vector2 B, float DegreeAngle)
		{
			return (float)(A.Length() * B.Length() * cos(DegreeAngle));
		}
		// 二つのベクトルの内積
		float InnerProduct(Vector2 A, Vector2 B)
		{
			return (A.x * B.x) + (A.y * B.y);
		}

		// ベクトルの引き算
		Vector2 SubVector(Vector2 A, Vector2 B)
		{
			return A - B;
		}
	private:
		static Collistions* m_instans;
	};
}
#endif // UTILITY