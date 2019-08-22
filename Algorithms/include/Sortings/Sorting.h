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
		using type = typename Iter::value_type;
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

	template<typename Iter>
	void merge(Iter first_begin, Iter first_end,
				Iter second_begin, Iter second_end, 
				Iter out_begin)
	{
		while (first_begin < first_end && second_begin < second_end)
		{
			*out_begin++ = *first_begin < *second_begin ? *first_begin++ : *second_begin++;
		}
		while (first_begin < first_end)
		{
			*out_begin++ = *first_begin++;
		}
		while (second_begin < second_end)
		{
			*out_begin++ = *second_begin++;
		}
	}

	template<typename Iter>
	void MergeSort(Iter first, Iter last)
	{
		int size = std::distance(first, last);
		if (size == 1)
			return;
		int half = size / 2;
		using type = typename Iter::value_type;
		Iter mid = first;
		std::advance(mid, half);
		std::vector<type> f_v(first, mid);
		std::vector<type> s_v(mid, last);
		MergeSort(f_v.begin(), f_v.end());
		MergeSort(s_v.begin(), s_v.end());
		merge(f_v.begin(), f_v.end(), s_v.begin(), s_v.end(), first);
	}

	template<typename Iter>
	Iter partition(Iter first, Iter last)
	{
		typename Iter::value_type pivot = *first;
		Iter out = first;

		for (Iter temp = std::next(first); temp != last; temp = std::next(temp))
		{
			if (*temp < pivot)
			{
				out = std::next(out);
				std::iter_swap(out, temp);
			}
		}
		std::iter_swap(out, first);
		return out;
	}
	
	template<typename Iter>
	void QuickSort(Iter first, Iter last)
	{
		if (std::distance(first, last) > 1)
		{
			Iter mid = partition(first, last);
			QuickSort(first, mid);
			QuickSort(std::next(mid), last);
		}
	}
}