#include <iostream>
#include "Utils.h"

int main()
{
    cin_vec_int(n, vec);
    sum_vec(vec, sum, long long);
    long long ans = sum * vec[0];
    sum -= vec[0];
    for (int i = 1; i < n; ++i)
    {
        ans += sum * (vec[i - 1] + vec[i]);
        sum -= vec[i];
    }
    std::cout << ans << std::endl;
    // cout_vec(vec);
}




