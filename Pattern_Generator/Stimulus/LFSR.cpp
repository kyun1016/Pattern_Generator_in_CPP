#include "LFSR.h"

namespace PARK
{
	LFSR::LFSR(const int& maxLFSR, const int& maxXOR, const std::vector<int>& XOR)
		: mMaxLFSR(maxLFSR)
		, mMaxXOR(maxXOR)
		, mXOR(XOR)
	{
		mLFSR.resize(maxLFSR, true);
	}
	void LFSR::Reset()
	{
		for (int i = 0; i < mMaxLFSR; ++i)
		{
			mLFSR[i] = true;
		}
	}
	void LFSR::Oper()
	{
		bool top = mLFSR[mMaxLFSR - 1];
		for (int i = 1; i < mMaxLFSR; ++i)
		{
			mLFSR[i] = mLFSR[i - 1];
		}

		mLFSR[0] = top;
		for (int i = 0; i < mMaxXOR; ++i)
		{
			mLFSR[mXOR[i]] = mLFSR[mXOR[i]] ^ top;
		}
	}
	void LFSR::Oper(const int& count)
	{
		for (int i = 0; i < count; ++i)
		{
			Oper();
		}
	}
	const std::vector<bool> LFSR::GetLFSR() const
	{
		return mLFSR;
	}
}