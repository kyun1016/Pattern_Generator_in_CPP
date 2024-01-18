#pragma once
#include <vector>

#define Assert(expression, message) assert(expression && message)

namespace PARK
{
	class Pixel final
	{
	public:
		Pixel() = delete;
		~Pixel() = delete;

		enum
		{
			BLACK = 0,
			RED = 1,
			GREEN = 2,
			YELLOW = 3,
			BLUE = 4,
			MAGENTA = 5,
			CYAN = 6,
			WHITE = 7,
			H_RAMP = 8,
			H_RAMP_PIXEL = 9,
			H_RAMP_PIXEL2 = 10,
			V_RAMP = 11,
			V_RAMP_PIXEL = 12,
			ONE_DOT = 13
		};

		static std::vector<int> getLine(const int& bitDepth, const int& maxLine, const int& maxPixel, const int& curLine, const int& type)
		{
			std::vector<int> ret;
			ret.reserve(maxPixel * 3);
			int r;
			int g;
			int b;
			int maxValue = (1 << bitDepth) - 1;
			int maxMod = (1 << bitDepth);

			for (int i = 0; i < maxPixel; i = ++i)
			{
				switch (type)
				{
				case BLACK:
					r = 0;
					g = 0;
					b = 0;
					break;
				case RED:
					r = maxValue;
					g = 0;
					b = 0;
					break;
				case GREEN:
					r = 0;
					g = maxValue;
					b = 0;
					break;
				case YELLOW:
					r = maxValue;
					g = maxValue;
					b = 0;
					break;
				case BLUE:
					r = 0;
					g = 0;
					b = maxValue;
					break;
				case MAGENTA:
					r = maxValue;
					g = 0;
					b = maxValue;
					break;
				case CYAN:
					r = 0;
					g = maxValue;
					b = maxValue;
					break;
				case WHITE:
					r = maxValue;
					g = maxValue;
					b = maxValue;
					break;
				case H_RAMP:
					r = static_cast<int>((static_cast<float>(i) / maxPixel) * maxValue);
					g = static_cast<int>((static_cast<float>(i) / maxPixel) * maxValue);
					b = static_cast<int>((static_cast<float>(i) / maxPixel) * maxValue);
					break;
				case H_RAMP_PIXEL:
					r = i % maxMod;
					g = (i + 1) % maxMod;
					b = (i + 2) % maxMod;
					break;
				case H_RAMP_PIXEL2:
					r = (i + curLine) % maxMod;
					g = (i + 1 + curLine) % maxMod;
					b = (i + 2 + curLine) % maxMod;
					break;
				case V_RAMP:
					r = static_cast<int>((static_cast<float>(curLine) / maxLine) * maxValue);
					g = static_cast<int>((static_cast<float>(curLine) / maxLine) * maxValue);
					b = static_cast<int>((static_cast<float>(curLine) / maxLine) * maxValue);
					break;
				case V_RAMP_PIXEL:
					r = curLine % maxMod;
					g = curLine % maxMod;
					b = curLine % maxMod;
					break;
				case ONE_DOT:
					if (i % 2)
					{
						r = 0;
						g = 0;
						b = 0;
					}
					else
					{
						r = maxValue;
						g = maxValue;
						b = maxValue;
					}
					break;
				default:
					Assert(false, "not supported input");
					break;
				}

				ret.push_back(r);
				ret.push_back(g);
				ret.push_back(b);
			}

			return ret;
		}
	};
}