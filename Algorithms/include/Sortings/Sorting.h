#pragma once


class Sorting
{
public:
	template<typename Iter>
	virtual void sort(const Iter& first, const Iter& second) = 0;
};