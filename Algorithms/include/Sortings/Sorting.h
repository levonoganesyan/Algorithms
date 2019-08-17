#pragma once
#include<iterator>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<functional>
namespace algo
{
	//template<typename Iter>
	//void sort(const Iter& first, const Iter& second);

	template<typename Iter>
	void BubbleSort(Iter first, Iter last)
	{
		for (Iter i = first; i != last; i = std::next(i))
		{
			for (Iter j = first; j < i; j = std::next(j))
			{
				if (*i < *j)
				{
					std::iter_swap(i, j);
				}
			}
		}
	}
	template<typename Iter>
	void SelectionSort(Iter first, Iter last)
	{
		for (Iter i = first; i != last; i = std::next(i))
		{
			Iter min = i;
			for (Iter j = i; j < last; j = std::next(j))
			{
				if (*j < *min)
				{
					min = j;
				}
			}
			std::iter_swap(i, min);
		}
	}

	template<typename Iter>
	void InsertionSort(Iter first, Iter last)
	{
		for (Iter i = std::next(first); i != last; i = std::next(i))
		{
			Iter temp = i;
			while (temp != first)
			{
				if (*temp < *std::prev(temp))
				{
					std::iter_swap(temp, std::prev(temp));
				}
				temp = std::prev(temp);
			}
		}
	}

	template<typename Iter>
	void RadixSort(Iter first, Iter last)
		// this sort must work only for ints
	{
		std::vector<int> vec(first, last); 
		int power_of_ten = 1;
		std::vector<std::vector<int>> buckets(10);
		for (int pow = 0; pow < 10; ++pow)
		{
			for (Iter i = vec.begin(); i != vec.end(); i = std::next(i))
			{
				buckets[(*i) / power_of_ten % 10].push_back(*i);
			}
			vec.clear();
			for (int i = 0; i < buckets.size(); ++i)
			{
				vec.insert(vec.end(), buckets[i].begin(), buckets[i].end());
				buckets[i].clear();
			}
			power_of_ten *= 10;
		}
		std::copy(vec.begin(), vec.end(), first);
	}
	template<typename Iter>
	void HeapSort(Iter first, Iter last)
	{
		using type = Iter::value_type;
		std::priority_queue<type, 
							std::vector<type>, 
							std::greater<type>> pq(first, last);
		while (!pq.empty())
		{
			*first = pq.top();
			first = std::next(first);
			pq.pop();
		}
	}



}