#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <sstream>
#pragma once

#include<iostream>
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
    Matrix<T> CreateMatrix(size_t n, T etalon = T());

    template <typename T>
    Matrix<T> CreateMatrix(size_t n, size_t m, T etalon = T());

    template <typename T>
    void CreateMatrix(Matrix<T>& matrix, size_t n, T etalon = T());

    template <typename T>
    void CreateMatrix(Matrix<T>& matrix, size_t n, size_t m, T etalon = T());

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
    inline Matrix<T> CreateMatrix(size_t n, T etalon)
    {
        return Matrix<T>(n, std::vector<T>(n, etalon));
    }

    template<typename T>
    inline Matrix<T> CreateMatrix(size_t n, size_t m, T etalon)
    {
        return Matrix<T>(n, std::vector<T>(m, etalon));
    }

    template<typename T>
    inline void CreateMatrix(Matrix<T>& matrix, size_t n, T etalon)
    {
        matrix = Matrix<T>(n, std::vector<T>(n, etalon));
    }

    template<typename T>
    inline void CreateMatrix(Matrix<T>& matrix, size_t n, size_t m, T etalon)
    {
        matrix = Matrix<T>(n, std::vector<T>(m, etalon));
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





#include<functional>
// TODO check math
namespace algo
{
    template<typename T>
    T gcd(T a, T b)
    {
        return b ? a : gcd(b, a % b);
    }

    template<typename T>
    T lcm(T a, T b)
    {
        return a / gcd(a, b) * b;
    }

    int euler_function(int n)
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            ans += gcd(i, n) == 1;
        }
        return ans;
    }
    
    template<typename T, typename Func>
    T bin_pow(T elem, int n, T neutral_element, 
                            Func mul = std::multiplies<T>())
    {
        T ans = neutral_element;
        while (n)
        {
            if (n & 1)
            {
                ans = mul(ans, elem);
            }
            elem = mul(elem, elem);
            n >>= 1;
        }
        return ans;
    }
    template<typename T, typename Func>
    T bin_pow(T elem, int n, int mod, T neutral_element, 
                                      Func mul = std::multiplies<T>(),
                                      Func modulus = std::modulus<T>())
    {
        T ans = neutral_element;
        while (n)
        {
            if (n & 1)
            {
                ans = mul(ans, elem);
                ans = modulus(ans, mod);
            }
            elem = mul(elem, elem);
            elem = modulus(elem, mod);
            n >>= 1;
        }
        return ans;
    }

    template<typename T>
    algo::Matrix<T> matrix_mul(const algo::Matrix<T>& l, const algo::Matrix<T>& r)
    {
        if (l[0].size() != r.size())
        {
            throw std::runtime_error("Matrix dimensions must be equal");
        }
        algo::Matrix<T> matrix = CreateMatrix(l.size(), r[0].size(), 0);
        for (int i = 0; i < l.size(); ++i)
            for (int j = 0; j < r.size(); ++j)
                for (int k = 0; k < l[i].size(); ++k)
                    matrix[i][j] += l[i][k] * r[k][j];
        return matrix;

    }

    template<typename T>
    algo::Matrix<T> matrix_mod(algo::Matrix<T> matrix, int mod)
    {
        for (int i = 0; i < matrix.size(); ++i)
            for (int j = 0; j < matrix[i].size(); ++j)
                matrix[i][j] %= mod;
        return matrix;

    }

}




namespace algo
{
    int euler_function(int n)
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            ans += gcd(i, n) == 1;
        }
        return ans;
    }
}


using namespace std;

// Test z-function

int main()
{
    algo::Matrix<int> mat{ {1, 1}, { 1, 0 } };
    algo::Matrix<int> neutral{ {1, 0}, { 0, 1 } };
    algo::Matrix<int> fib { {1, 1} };
    mat = algo::bin_pow(mat, 7, neutral, algo::matrix_mul<int>);
    fib = algo::matrix_mul(fib, mat);
}



