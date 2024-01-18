#include "Line.h"

namespace PARK
{
	Line::Line(const int& maxHChannel, const int& maxHBlank)
		: mMaxHChannel(maxHChannel)
		, mMaxHBlank(maxHBlank)
		, mKFirst(0)
		, mKSecond(0)
		, mCtrlL(MAX_CTRL_L)
		, mCtrlF(MAX_CTRL_F)
		, mHChannel(maxHChannel)
		, mHBlank(maxHBlank)
	{
	}
}
