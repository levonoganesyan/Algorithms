#pragma once
#include<algorithm>
namespace algo
{
    template<typename T, typename... Others>
    T max(T first, Others... others)
    {
        return std::max(first, max(others...));
    }
    template<typename T>
    T max(T first)
    {
        return first;
    }
}



