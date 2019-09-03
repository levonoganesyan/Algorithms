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

    int EulerFunction(int n)
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
}




namespace algo
{

}


using namespace std;

// Test z-function

int main()
{
    int a, n;
    cin >> a >> n;
    std::cout << algo::bin_pow(a, n);
}



