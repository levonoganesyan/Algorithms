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
		for (Iter i = first; i != last; std::next(i))
		{
			for (Iter j = first; j < i; std::next(j))
				if (*i < *j)
					std::iter_swap(i, j);
			for (Iter i = first; i != last; i++)
				std::cout << *i << " ";
			std::cout << std::endl;
		}
	}




}