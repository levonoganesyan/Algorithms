#pragma once
#include<algorithm>
#include "Utils.h"
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

    template<typename T, typename... Others>
    T min(T first, Others... others)
    {
        return std::min(first, min(others...));
    }
    template<typename T>
    T min(T first)
    {
        return first;
    }

    template<typename Container, typename T>
    void sum_container(const Container& container, T& sum)
    {
        for (auto& elem : container)
        {
            sum += elem;
        }
    }

    template<typename T>
    Matrix<T> createMatrix(size_t n, size_t m, T etalon = T())
    {
        return Matrix(n, std::vector<T>(m, etalon));
    }
    
    template<typename Container>
    void input_container(std::istream& in,
                         int& n,
                         Container& container)
    {
        in >> n;
        container.resize(n);
        for (auto& elem : container)
        {
            in >> elem;
        }
    }
    
    template<typename Container>
    void output_container(std::ostream& out,
                          const Container& container,
                          const std::string& delimiter)
    {
        for (auto& elem : container)
        {
            out << elem << delimiter;
        }
    }
}



