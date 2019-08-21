//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

std::vector<int> getRandomVector(int n, int min, int max)
{
	std::vector<int> random_vector(n);
	std::mt19937 rand_function(time(0));
	std::uniform_int_distribution<int> uid(min, max);
	for (auto& elem : random_vector)
	{
		elem = uid(rand_function);
	}
	return random_vector;
}