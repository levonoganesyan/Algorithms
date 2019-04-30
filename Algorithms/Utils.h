#pragma once
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
namespace algo
{
    template<typename T, typename... Others>
    T max(T first, Others... others);

    template<typename T>
    T max(T first);

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
        const std::string& delimiter = " ")
    {
        for (auto& elem : container)
        {
            out << elem << delimiter;
        }
    }

    /*
#define cr_int(n) int n
#define cr_vec(v) std::vector
    */

#define in_vec(in, n, c, t) \
        int n; \
        std::vector<t> c; \
        algo::input_container(in, n, c)

#define cin_vec(n, c, t) \
        in_vec(std::cin, n, c, t)

#define in_vec_int(in, n, c) \
        in_vec(in, n, c, int)


#define cin_vec_int(n, c) \
        cin_vec(n, c, int)


#define out_vec_delim(out, c, d) \
        algo::output_container(out, c, d)

#define out_vec(out, c) \
        algo::output_container(out, c)

#define cout_vec_delim(c, d) \
        algo::output_container(std::cout, c, d)

#define cout_vec(c, d) \
        algo::output_container(std::cout, c)

    template<typename Container, typename T>
    void sum_container(const Container& container, T& sum)
    {
        for (auto& elem : container)
        {
            sum += elem;
        }
    }
    #define sum_vec(c, s, t) \
        t s = 0; \
        algo::sum_container(c, s)
}

#include "Utils.hpp"


