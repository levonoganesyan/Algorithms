#pragma once
#include<algorithm>
namespace algo
{
    template<typename T, typename... Others>
    T max(T first, Others... others);

    template<typename T>
    T max(T first);
}

#include "Utils.hpp"


