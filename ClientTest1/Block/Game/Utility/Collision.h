#pragma once

#include<SimpleMath.h>
#include"SingletonBase.h"


#define PAI 3.14159265258979323846264338327950288

namespace Utility
{
	template<typename T>bool CollisionT(T& t, T min,T max)
	{
		if (t <= min)
		{
			return true;
		}
		else if (t >= max)
		{
			return true;
		}
		return false;
	};

	class Collision
	{
	public:
		Collision(float x, float y, float w, float h) { mPos = DirectX::SimpleMath::Vector2(x, y);	mWidth = w;	mHeight = h;	SetPositions(); }


		void SetPos(float x, float y) { mPos = DirectX::SimpleMath::Vector2(x, y); SetPositions(); }
		void SetPositions()
		{
			mUR = DirectX::SimpleMath::Vector2(mPos.x + (mWidth *0.45f), mPos.y - (mHeight *0.45f));
			mBR = DirectX::SimpleMath::Vector2(mPos.x + (mWidth *0.45f), mPos.y + (mHeight *0.45f));
			mUL = DirectX::SimpleMath::Vector2(mPos.x - (mWidth *0.45f), mPos.y - (mHeight *0.45f));
			mBL = DirectX::SimpleMath::Vector2(mPos.x - (mWidth *0.45f), mPos.y + (mHeight *0.45f));


			mBC = DirectX::SimpleMath::Vector2(mPos.x, mPos.y + (mHeight *0.45f));
			mUC = DirectX::SimpleMath::Vector2(mPos.x, mPos.y - (mHeight *0.45f));
			mLC = DirectX::SimpleMath::Vector2(mPos.x - (mWidth *0.45f), mPos.y);
			mRC = DirectX::SimpleMath::Vector2(mPos.x + (mWidth *0.45f), mPos.y);

		}
	
		// 点と矩形の判定
		bool IsHitCheck(Collision& col,int i) 
		{
			DirectX::SimpleMath::Vector2 A;
			DirectX::SimpleMath::Vector2 B;
			switch (i)
			{
			case 0:		// 左
				A = col.mUR - col.mRC;
				B = this->mLC - col.mRC;
				if (A.Length() < B.Length()) { return false; }
				if (col.mBL.x > this->mPos.x) { return false; }
				return true;
				break;
			case 1:		// 右
				A = col.mUL - col.mLC;
				B = this->mRC - col.mLC;
				if (A.Length() < B.Length()) { return false; }
				if (col.mLC.x < this->mPos.x) { return false; }
				return true;
				break;
			case 2:		// 上
				A = col.mBL - col.mBC;
				B = this->mUC - col.mBC;
				if (A.Length() < B.Length()) { return false; }
				if (col.mBC.y < this->mPos.y) { return false; }
				if (col.mUC.y > this->mPos.y) { return false; }
				return true;
				break;
			case 3:		// 下
				A = col.mUL - col.mUC;
				B = this->mBC - col.mUC;
				if (A.Length() < B.Length()) { return false; }
				if (col.mUC.y > this->mPos.y) { return false; }
				if (col.mBC.y < this->mPos.y) { return false; }
				return true;
				break;

			default:
				return false;
				break;
			}
			
		}

	private:
		DirectX::SimpleMath::Vector2 mBR;
		DirectX::SimpleMath::Vector2 mBL;
		DirectX::SimpleMath::Vector2 mUR;
		DirectX::SimpleMath::Vector2 mUL;

		DirectX::SimpleMath::Vector2 mBC;
		DirectX::SimpleMath::Vector2 mUC;
		DirectX::SimpleMath::Vector2 mLC;
		DirectX::SimpleMath::Vector2 mRC;

		float mWidth;
		float mHeight;
		DirectX::SimpleMath::Vector2 mPos;

	};

	class SingltonCollision:public Utility::SingletonBase<SingltonCollision>
	{

	public:
		friend Utility::SingletonBase<SingltonCollision>;

		// 円と線分のあたり判定
		bool HitLineAndCircle(DirectX::SimpleMath::Vector2 _lineStart/*線分の始点*/, DirectX::SimpleMath::Vector2 _lineEnd/*線分の終点*/, DirectX::SimpleMath::Vector2 _circlePos/*円の中心*/, float _radius/*半径*/)
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
		// 円と円のあたり判定
		bool HitCircleAndCircle(DirectX::SimpleMath::Vector2 _circle1Pos, float _radius1, DirectX::SimpleMath::Vector2 _circle2Pos, float _radius2)
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
		// 円と点のあたり判定
		bool HitCircleAndPoint(DirectX::SimpleMath::Vector2 _point, DirectX::SimpleMath::Vector2 _circlePos, float _radius)
		{
			float x = (_point.x - _circlePos.x)*(_point.x - _circlePos.x);
			float y = (_point.y - _circlePos.y)*(_point.y - _circlePos.y);

			if (x + y <= _radius*_radius)
			{
				return true;
			}
			return false;
		}
		// 三角形と点のあたり判定
		bool HitTriangleAndPoint(DirectX::SimpleMath::Vector2 _point, DirectX::SimpleMath::Vector2 _triPosA, DirectX::SimpleMath::Vector2 _triPosB, DirectX::SimpleMath::Vector2 _triPosC)
		{
			using namespace DirectX::SimpleMath;
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
		SingltonCollision() {}


		// 円と線分　START
		DirectX::SimpleMath::Vector2 mLineSegment;		// 線分ベクトル

		DirectX::SimpleMath::Vector2 mStartToCircle;	// 線分の始点から円の中心までのベクトル
		DirectX::SimpleMath::Vector2 mEndToCircle;		// 線分の終点から円の中心までのベクトル
 
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
		DirectX::SimpleMath::Vector2 Vectol(DirectX::SimpleMath::Vector2 start , DirectX::SimpleMath::Vector2 end)
		{
			DirectX::SimpleMath::Vector2 vec = end - start;
			return vec;
		}

		// ベクトル同士のなす角(デグリー角出力)
		float DegreeAngle(DirectX::SimpleMath::Vector2 A, DirectX::SimpleMath::Vector2 B)
		{
			double cos;

			cos = ((A.x*B.x) + (A.y*B.y)) / (A.Length()*B.Length());
			cos = ((A.x*B.x) + (A.y*B.y)) / (A.Length()*B.Length());
			float radian = (float)acos(cos);
			float degree = (float)(radian*(180 / PAI));
			return degree;
		}
		// ベクトル同士のなす角(ラジアン角出力)
		float RadianAngle(DirectX::SimpleMath::Vector2 A, DirectX::SimpleMath::Vector2 B)
		{
			double cos;
			cos = ((A.x*B.x) + (A.y*B.y)) / (A.Length()*B.Length());
			float radian = (float)acos(cos);
			return radian;
		}

		// 二つのベクトルの内積
		float InnerProduct(DirectX::SimpleMath::Vector2 A, DirectX::SimpleMath::Vector2 B,float DegreeAngle)
		{
			return A.Length() * B.Length() * cos(DegreeAngle);
		}
		// 二つのベクトルの内積
		float InnerProduct(DirectX::SimpleMath::Vector2 A, DirectX::SimpleMath::Vector2 B)
		{
			return (A.x * B.x) + (A.y * B.y);
		}

		// ベクトルの引き算
		DirectX::SimpleMath::Vector2 SubVector(DirectX::SimpleMath::Vector2 A, DirectX::SimpleMath::Vector2 B)
		{
			return A - B;
		}
	};

}