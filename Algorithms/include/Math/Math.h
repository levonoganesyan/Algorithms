#pragma once

#include<iostream>
#include<Utils.h>
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

    template<typename T>
    T bin_pow(T elem, int n)
    {
        T ans = 1;
        while (n)
        {
            if (n & 1)
            {
                ans *= elem;
            }
            elem *= elem;
            std::cout << elem << std::endl;
            n >>= 1;
        }
        return ans;
    }
    template<typename T>
    T bin_pow(T elem, int n, int mod)
    {
        T ans = 1;
        while (n)
        {
            if (n & 1)
            {
                ans *= elem;
                ans %= mod;
            }
            elem *= elem;
            elem %= mod;
            n >>= 1;
        }
        return ans;
    }

    template<typename T>
    T matrix_mul
    {

    }

}


