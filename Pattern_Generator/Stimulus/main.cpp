#include <cAssert>
#include <iostream>
#include <memory>
#include <vector>
#include "Line.h"
#include "Frame.h"
#include "PPM.h"

#define Assert(expression, message) assert(expression && message)

int main(int argc, char* argv[])
{
	const int MAX_H_PIXEL = 1920;
	const int MAX_H_CHANNEL = MAX_H_PIXEL * 3;
	const int MAX_H_BLANK = 14;
	const int MAX_V_PIXEL = 1080;
	const int MAX_V_BLANK = 16;
	const int MAX_LFSR = 24;
	const int MAX_LFSR_XOR = 3;
	const int MAX_CTRL_L = 5;
	const int MAX_CTRL_F = 60;
	const int BIT_DEPTH = 8;

	//======================================================================================
	// start LFSR random setting
	std::vector<int> xorPosition;
	xorPosition.reserve(MAX_LFSR_XOR);
	for (int i = 0; i < MAX_LFSR_XOR; ++i)
	{
		int temp = rand() % MAX_LFSR;
		bool flag = true;
		for (int j = 0; j < xorPosition.size(); j++)
		{
			if (xorPosition[j] == temp)
			{
				flag = false;
			}
		}
		if (flag)
		{
			xorPosition.push_back(temp);
		}
		else
		{
			--i;
			continue;
		}
	}

	std::shared_ptr<PARK::LFSR> lfsr;
	lfsr = std::make_shared<PARK::LFSR>(MAX_LFSR, MAX_LFSR_XOR, xorPosition);
	// finish LSFR random setting
	//======================================================================================

	// Case 1. Manual Setting
	{
		PARK::Frame frame(BIT_DEPTH, MAX_V_PIXEL, MAX_V_BLANK, MAX_H_PIXEL, MAX_H_BLANK, lfsr);

		//======================================================================================
		// start Data setting
		std::vector<int> ctrlL;
		std::vector<int> ctrlF;
		std::vector<int> pixel;
		std::vector<int> blank;
		ctrlL.resize(MAX_CTRL_L, 0);		// Default all 0
		ctrlF.resize(MAX_CTRL_F, 0);		// Default all 0
		pixel.reserve(MAX_H_CHANNEL);
		blank.resize(MAX_H_CHANNEL, 0);		// Default all 0
		for (int i = 0; i < MAX_H_CHANNEL; ++i)
		{
			pixel.push_back(i % (1 << BIT_DEPTH));
		}
		// finish Data setting
		//======================================================================================

		// Set Active Display Area
		for (int line = 0; line < MAX_V_PIXEL; ++line)
		{
			frame.ManualSetK(line, 1, 1);
			frame.ManualSetK(line, 2, 2);
			frame.ManualSetCtrlL(line, ctrlL);
			frame.ManualSetCtrlF(line, ctrlF);
			frame.ManualSetPixel(line, pixel);
		}

		// Set Vertical Blank Area
		for (int line = MAX_V_PIXEL; line < MAX_V_PIXEL + MAX_V_BLANK; ++line)
		{
			frame.ManualSetK(line, 1, 0);
			frame.ManualSetK(line, 2, 0);
			frame.ManualSetCtrlL(line, ctrlL);
			frame.ManualSetCtrlF(line, ctrlF);
			frame.ManualSetPixel(line, blank);
		}

		PARK::PPM::printPPM("mannuel", frame);
	}

	// Case 2. Manual & Auto (pixel data) Setting
	{
		/*enum
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
			V_RAMP = 10,
			V_RAMP_PIXEL = 11,
			ONE_DOT = 12
		};*/

		// *********************************************************************
		// *** Change this Part ***
		const int IMAGE_TYPE = 10;
		const std::string FILE_NAME = "H_RAMP_PIXEL2";
		// *** Change this part ***
		// *********************************************************************

		PARK::Frame frame(BIT_DEPTH, MAX_V_PIXEL, MAX_V_BLANK, MAX_H_PIXEL, MAX_H_BLANK, lfsr);

		//======================================================================================
		// Data setting
		std::vector<int> ctrlL;
		std::vector<int> ctrlF;
		std::vector<int> blank;
		ctrlL.resize(MAX_CTRL_L, 0);		// Default all 0
		ctrlF.resize(MAX_CTRL_F, 0);		// Default all 0
		blank.resize(MAX_H_CHANNEL, 0);		// Default all 0
		//======================================================================================

		// Set Active Display Area
		for (int line = 0; line < MAX_V_PIXEL; ++line)
		{
			frame.ManualSetK(line, 1, 1);
			frame.ManualSetK(line, 2, 2);
			frame.ManualSetCtrlL(line, ctrlL);
			frame.ManualSetCtrlF(line, ctrlF);
			frame.SetPixel(line, IMAGE_TYPE);	// Automated image generation
		}

		// Set Vertical Blank Area
		for (int line = MAX_V_PIXEL; line < MAX_V_PIXEL + MAX_V_BLANK; ++line)
		{
			frame.ManualSetK(line, 1, 0);
			frame.ManualSetK(line, 2, 0);
			frame.ManualSetCtrlL(line, ctrlL);
			frame.ManualSetCtrlF(line, ctrlF);
			frame.ManualSetPixel(line, blank);
		}

		PARK::PPM::printPPM(FILE_NAME, frame);
	}
}