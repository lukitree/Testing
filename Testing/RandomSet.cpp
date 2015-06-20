#include "RandomSet.h"


namespace RND
{
	int Int(int lower, int upper)
	{
		if (upper <= lower)
			return lower;

		static std::random_device rd;
		static std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(lower, upper);

		return dist(mt);
	}
}