#pragma once

#include <vector>

namespace PARK
{
	class LFSR final
	{
	public:
		LFSR(const int& maxLFSR, const int& maxXOR, const std::vector<int>& XOR); // bool is not 1bit
		~LFSR() = default;

		void Reset();
		void Oper();
		void Oper(const int& count);

		const std::vector<bool> GetLFSR() const;

	private:
		int mMaxLFSR;
		int mMaxXOR;
		std::vector<bool> mLFSR;
		std::vector<int> mXOR;
	};
}