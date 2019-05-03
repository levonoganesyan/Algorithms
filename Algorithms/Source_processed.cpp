#include <iostream>
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

#pragma once
#include<algorithm>
#include<random>
namespace algo
{
    template<typename T, typename... Others>
    inline T max(T first, Others... others)
    {
        return std::max(first, max<T>(others...));
    }
    template<typename T>
    inline T max(T first)
    {
        return first;
    }

    template<typename T, typename... Others>
    inline T min(T first, Others... others)
    {
        return std::min(first, min(others...));
    }
    template<typename T>
    inline T min(T first)
    {
        return first;
    }

    template<typename Container, typename T>
    inline void sum_container(const Container& container, T& sum)
    {
        for (auto& elem : container)
        {
            sum += elem;
        }
    }

    template<typename T>
    inline Matrix<T> createMatrix(size_t n, size_t m, T etalon)
    {
        return Matrix<T>(n, std::vector<T>(m, etalon));
    }

    inline double random(double min, double max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(min, max);
        return dist(mt);
    }
    
    template<typename Container>
    inline void input_container(std::istream& in,
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
    inline void output_container(std::ostream& out,
                          const Container& container,
                          const std::string& delimiter)
    {
        for (auto& elem : container)
        {
            out << elem << delimiter;
        }
    }
}





#pragma once


namespace algo
{

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

#define sum_vec(c, s, t) \
        t s = 0; \
        algo::sum_container(c, s)

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

}


//int main()
//{
//   
//}
//
//


