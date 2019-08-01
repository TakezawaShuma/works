#pragma once

namespace Utility
{
	class Flag
	{
	public:

		// コンストラクタ
		Flag()
			: mFlag(0)
		{

		}

		/// <summary>
		/// フラグを立てる
		/// </summary>
		void On(unsigned int flag)
		{
			mFlag |= flag;
		}

		/// <summary>
		/// フラグを伏せる
		/// </summary>
		/// <param name="flag"></param>
		void Off(unsigned int flag)
		{
			mFlag &= ~flag;
		}
		
		/// <summary>
		/// フラグが立ってるか確認
		/// </summary>
		/// <param name="flag"></param>
		/// <returns>true = 立ってる　false = 立ってない</returns>
		bool Is(unsigned int flag)
		{
			return (mFlag & flag) != 0;
		}

	private:

		unsigned int mFlag;
	};
}