#pragma once
#include<iterator>

namespace algo
{
	//template<typename Iter>
	//void sort(const Iter& first, const Iter& second);

	template<typename Iter>
	void BubbleSort(const Iter& first, const Iter& last)
	{
		Iter temp = first;
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
			}
			last = std::prev(last);
		}
	}




}