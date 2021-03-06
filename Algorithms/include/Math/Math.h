#pragma once

#include<iostream>
#include<Utils.h>
#include<functional>
// TODO check math
namespace algo
{
    template<typename T>
    inline T gcd(T a, T b)
    {
        return b ? gcd(b, a % b) : a;
    }

    template<typename T>
    inline T lcm(T a, T b)
    {
        return a / gcd(a, b) * b;
    }

    inline int euler(int n)
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            ans += gcd(i, n) == 1;
        }
        return ans;
    }
    inline long long fast_euler(long long n)
    {
        long long ans = n;
        long long prime = 2;
        while (n >= prime * prime)
        {
            if (n % prime == 0)
            {
                ans = ans / prime * (prime - 1);
                while (n % prime == 0)
                    n /= prime;
            }
            ++prime;
        }
        if (n != 1)
            ans = ans / n * (n - 1);
        return ans;
    }
    
    template<typename T>
    inline T bin_pow(T elem, int n)
    {
        T ans = 1;
        while (n)
        {
            if (n & 1)
            {
                ans = ans * elem;
            }
            elem = elem * elem;
            n >>= 1;
        }
        return ans;
    }

    template<typename T, typename Func>
    inline T bin_pow(T elem, int n, T neutral_element,
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
    inline T bin_pow(T elem, int n, int mod, T neutral_element,
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
    inline algo::Matrix<T> matrix_mul(const algo::Matrix<T>& l,
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
    inline algo::Matrix<T> matrix_mod(algo::Matrix<T> matrix, int mod)
    {
        for (int i = 0; i < matrix.size(); ++i)
            for (int j = 0; j < matrix[i].size(); ++j)
                matrix[i][j] %= mod;
        return matrix;

    }

    inline std::vector<int> sieve_of_eratosthenes(int n)
    {
        std::vector<int> primes(1, 2);
        std::vector<char> used(n, false);
        for (int i = 2; i < used.size(); i += 2)
            used[i] = true;
        for (long long i = 3; i < used.size(); i += 2)
        {
            if (!used[i])
            {
                primes.push_back(i);
                for (long long j = i * i; j < used.size(); j += i)
                {
                    used[j] = true;
                }
            }
        }
        return primes;
    }
    inline int extended_euclidean(int a, int b, int& x, int& y)
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


