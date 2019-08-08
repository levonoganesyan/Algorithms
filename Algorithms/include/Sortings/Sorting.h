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
		/*Iter temp = first;
		bool need_to_continue = true;
		while (need_to_continue)
		{
			need_to_continue = false;
			while (std::next(first) != last)
			{
				need_to_continue = true;
				Iter& next = std::next(first);
				if (*next < *first)
				{
					std::swap(*next, *first);
				}
				first = next;
			}
			last = std::prev(last);
		}*/
		for (Iter i = first; i != last; i++)
		{
			for (Iter j = first; j < i; j++)
				if (*i < *j)
					std::iter_swap(i, j);
			for (Iter i = first; i != last; i++)
				std::cout << *i << " ";
		}
	}




}