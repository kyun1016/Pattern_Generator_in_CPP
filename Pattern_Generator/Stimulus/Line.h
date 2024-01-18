#pragma once

#include <vector>

namespace PARK
{
	enum
	{
		MAX_CTRL_L = 5,
		MAX_CTRL_F = 60
	};

	class Line
	{
	public:
		Line(const int& maxHChannel, const int& maxHBlank);
		~Line() = default;

		int mKFirst;					// only K1, 2, 3, 4
		int mKSecond;					// only K1, 2, 3, 4
		std::vector<int> mCtrlL;
		std::vector<int> mCtrlF;
		std::vector<int> mHChannel;
		std::vector<int> mHBlank;
	private:
		int mMaxHChannel;
		int mMaxHBlank;
	};
}

