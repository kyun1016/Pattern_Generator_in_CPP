#pragma once

#include <vector>
#include <memory>
#include <cAssert>

#include "Line.h"
#include "LFSR.h"
#include "Pixel.h"

namespace PARK
{
	class Frame
	{
	public:
		Frame(const int& maxBitDepth, const int& maxVPixel, const int& maxVBlank, const int& maxHPixel, const int& maxHBlank, std::shared_ptr<LFSR> lfsr);
		~Frame() = default;

		// Manual Setting
		void ManualSetK(const int& line, const int& pos, const int& type);
		void ManualSetCtrlL(const int& line, const std::vector<int>& data);
		void ManualSetPixel(const int& line, const std::vector<int>& data);
		void ManualSetCtrlF(const int& line, const std::vector<int>& data);
		
		// Auto Setting
		void SetK1(const int& line, const int& pos);
		void SetK2(const int& line, const int& pos);
		void SetK3(const int& line, const int& pos);
		void SetK4(const int& line, const int& pos);

		void SetPixel(const int& line, const int& type);

		void SetLine(const int& line);
		void SetFrame();

		void Scramble(const int& line, const int& pixel);

		int getBitDepth() const;
		int getMaxVPixel() const;
		int getMaxVBlank() const;
		int getMaxHPixel() const;
		int getMaxHBlank() const;

		std::vector<std::unique_ptr<Line>> mVPixel;
		std::vector<std::unique_ptr<Line>> mVBlank;
	private:
		int mBitDepth;
		int mMaxVPixel;
		int mMaxVBlank;
		int mMaxHPixel;
		int mMaxHBlank;

		std::shared_ptr<LFSR> mLFSR;
	};
}


