#pragma once

#include<iostream>
#include<Utils.h>
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
    algo::Matrix<T> matrix_mul(const algo::Matrix<T>& l, 
                                const algo::Matrix<T>& r)
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

    std::vector<int> sieve_of_eratosthenes(int n)
    {
        std::vector<int> primes(1, 2);
        std::vector<char> used(n, false);
        for (int i = 2; i < used.size(); i += 2)
            used[i] = true;
        for (int i = 3; i < used.size(); i += 2)
        {
            if (!used[i])
            {
                primes.push_back(i);
                for (int j = i * i; j < used.size(); j += i)
                {
                    used[j] = true;
                }
            }
        }
        return primes;
    }
    int extended_euclidean(int a, int b, int& x, int& y)
    {
        if (a == 0)
        {
            x = 0, y = 1;
            return b;
        }
        int x1, y1;
        int gcd = extended_euclidean(b % a, a, x1, y1);
        x = y1 - b / a * x1;
        y = x1;
        return gcd;
    }
}


