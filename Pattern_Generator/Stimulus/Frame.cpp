#include "Frame.h"
namespace PARK
{
	Frame::Frame(const int& maxBitDepth, const int& maxVPixel, const int& maxVBlank, const int& maxHPixel, const int& maxHBlank, std::shared_ptr<LFSR> lfsr)
		: mBitDepth(maxBitDepth)
		, mMaxVPixel(maxVPixel)
		, mMaxVBlank(maxVBlank)
		, mMaxHPixel(maxHPixel)
		, mMaxHBlank(maxHBlank)
		, mLFSR(lfsr)
	{
		mVPixel.reserve(mMaxVPixel);
		mVBlank.reserve(mMaxVBlank);

		for (int i = 0; i < mMaxVPixel; ++i)
		{
			mVPixel.push_back(std::move(std::make_unique<Line>(maxHPixel*3, maxHBlank)));
		}

		for (int i = 0; i < mMaxVBlank; ++i)
		{
			mVBlank.push_back(std::move(std::make_unique<Line>(maxHPixel*3, maxHBlank)));
		}
	}

	void Frame::ManualSetK(const int& line, const int& pos, const int& type)
	{
		Assert(type >= 0 && type <= 4, "K Symbol type is 0~4");

		if (line < mMaxVPixel)
		{
			if (pos == 1)
			{
				mVPixel[line]->mKFirst = type;
			}
			else if (pos == 2)
			{
				mVPixel[line]->mKSecond = type;
			}
			else
			{
				Assert(false, "K position is 1 or 2");
			}
		}
		else
		{
			if (pos == 1)
			{
				mVBlank[line - mMaxVPixel]->mKFirst = type;
			}
			else if (pos == 2)
			{
				mVBlank[line - mMaxVPixel]->mKSecond = type;
			}
			else
			{
				Assert(false, "K position is 1 or 2");
			}
		}

	}
	void Frame::ManualSetCtrlL(const int& line, const std::vector<int>& data)
	{
		Assert(data.size() >= MAX_CTRL_L, "CTRL_L data is bigger than 5");
		if (line < mMaxVPixel)
		{
			for (size_t i = 0; i < MAX_CTRL_L; ++i)
			{
				mVPixel[line]->mCtrlL[i] = data[i];
			}
		}
		else
		{
			for (size_t i = 0; i < MAX_CTRL_L; ++i)
			{
				mVBlank[line - mMaxVPixel]->mCtrlL[i] = data[i];
			}
		}
	}
	void Frame::ManualSetPixel(const int& line, const std::vector<int>& data)
	{
		Assert(data.size() >= mMaxHPixel * 3, "Pixel data is bigger than max horizantal pixel * 3");
		if (line < mMaxVPixel)
		{
			for (size_t i = 0; i < mMaxHPixel * 3; ++i)
			{
				mVPixel[line]->mHChannel[i] = data[i];
			}
		}
		else
		{
			for (size_t i = 0; i < mMaxHPixel; ++i)
			{
				mVBlank[line - mMaxVPixel]->mHChannel[i] = data[i];
			}
		}
	}
	void Frame::ManualSetCtrlF(const int& line, const std::vector<int>& data)
	{
		Assert(data.size() >= MAX_CTRL_F, "CTRL_L data is bigger than 60");
		if (line < mMaxVPixel)
		{
			for (size_t i = 0; i < MAX_CTRL_F; ++i)
			{
				mVPixel[line]->mCtrlF[i] = data[i];
			}
		}
		else
		{
			for (size_t i = 0; i < MAX_CTRL_F; ++i)
			{
				mVBlank[line - mMaxVPixel]->mCtrlF[i] = data[i];
			}
		}
	}

	void Frame::SetK1(const int& line, const int& pos)
	{
		ManualSetK(line, pos, 1);
	}

	void Frame::SetK2(const int& line, const int& pos)
	{
		ManualSetK(line, pos, 2);
	}

	void Frame::SetK3(const int& line, const int& pos)
	{
		ManualSetK(line, pos, 3);
	}

	void Frame::SetK4(const int& line, const int& pos)
	{
		ManualSetK(line, pos, 4);
	}

	void Frame::SetPixel(const int& line, const int& type)
	{
		ManualSetPixel(line, Pixel::getLine(mBitDepth, mMaxVPixel, mMaxHPixel, line, type));
	}

	void Frame::SetLine(const int& line)
	{
	}

	void Frame::SetFrame()
	{
	}



	void Frame::Scramble(const int& line, const int& pixel)
	{
	}
	int Frame::getBitDepth() const
	{
		return mBitDepth;
	}
	int Frame::getMaxVPixel() const
	{
		return mMaxVPixel;
	}
	int Frame::getMaxVBlank() const
	{
		return mMaxVBlank;
	}
	int Frame::getMaxHPixel() const
	{
		return mMaxHPixel;
	}
	int Frame::getMaxHBlank() const
	{
		return mMaxHBlank;
	}
}
