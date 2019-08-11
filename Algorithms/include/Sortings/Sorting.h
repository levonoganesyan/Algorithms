#pragma once
#include<iterator>
#include<iostream>
namespace algo
{
	//template<typename Iter>
	//void sort(const Iter& first, const Iter& second);

	template<typename Iter>
	void BubbleSort(Iter first, Iter last)
	{
		for (Iter i = first; i != last; i = std::next(i))
			for (Iter j = first; j < i; j = std::next(j))
				if (*i < *j)
					std::iter_swap(i, j);
	}
	template<typename Iter>
	void SelectionSort(Iter first, Iter last)
	{
		for (Iter i = first; i != last; i = std::next(i))
		{
			Iter min = first;
			for (Iter j = i; j < last; j = std::next(j))
				if (*j < *min)
					min = j;
			std::iter_swap(i, min);

		}
	}




}