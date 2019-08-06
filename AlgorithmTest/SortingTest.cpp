#include"pch.h"

#include"Sortings/Sorting.h"
#include<vector>
#include<random>
#include<ctime>

std::vector<int> getRandomVector(int n, int min = -1000, int max = 1000)
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


TEST(SortingTest, SortingTest)
{
	{
		auto first = getRandomVector(1000);
		auto second = first;

	}
}