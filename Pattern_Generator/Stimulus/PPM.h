#pragma once
#include <string>
#include <fstream>
#include <iomanip>
#include "Frame.h"

namespace PARK
{
	class PPM final
	{
	public:
		PPM() = delete;
		~PPM() = delete;

		static void printPPM(const std::string& fileName, const Frame& frame)
		{
			std::ofstream of;
			of.open(fileName + ".ppm");
			if (of.is_open())
			{
				Assert(frame.getMaxHPixel() % 3 == 0, "pixel must be a multiple of 3");
				of << "P3" << std::endl;
				of << frame.getMaxHPixel() << " " << frame.getMaxVPixel() << std::endl;			// width, height
				of << (1 << frame.getBitDepth()) - 1 << std::endl;

				for (int line = 0; line < frame.getMaxVPixel(); ++line)
				{
					for (int ch = 0; ch < frame.getMaxHPixel() * 3; ch = ch + 3)
					{
						// lines should be limited to 70 characters (https://en.wikipedia.org/wiki/Netpbm#PPM_example)
						of << std::setw(3) << frame.mVPixel[line]->mHChannel[ch] << " " << std::setw(3) << frame.mVPixel[line]->mHChannel[ch + 1] << " " << std::setw(3) << frame.mVPixel[line]->mHChannel[ch + 2] << std::endl;
					}
					of << "\n";
				}
				of << std::endl;
			}
			of.close();
		};
	};
}