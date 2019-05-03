#pragma once
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<cassert>
#include<queue>
#include<set>
#include<map>

namespace algo
{
    const int Inf = INT_MAX;
    const long long LInf = LLONG_MAX;

    template<typename T, typename... Others>
    T max(T first, Others... others);

    template<typename T>
    T max(T first);

    template<typename T, typename... Others>
    T min(T first, Others... others);

    template<typename T>
    T min(T first);

    template<typename Container>
    void input_container(std::istream& in,
                         int& n,
                         Container& container);

    template<typename Container>
    void output_container(std::ostream& out,
                          const Container& container,
                          const std::string& delimiter = " ");

    template<typename Container, typename T>
    void sum_container(const Container& container, T& sum);


    template <typename T>
    using Matrix = std::vector<std::vector<T>>;

    template <typename T>
    Matrix<T> createMatrix(size_t n, size_t m, T etalon = T());

    double random(double min, double max);
}

#include "Utils.hpp"


