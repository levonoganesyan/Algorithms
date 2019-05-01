#include <iostream>
#include "Utils.h"
#include "Defines.h"
bool foo(std::vector<int> vec, bool b)
{
    auto original = vec;
    if(b)   
        std::sort(all(vec));
    else
        std::sort(rall(vec));

    int f = -1;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] != original[i])
        {
            if (f == -1)
            {
                f = i;
            }
            else
            {
                std::swap(vec[i], vec[f]);
                if (vec == original)
                {
                    std::cout << "Yes" << std::endl
                        << f + 1 << " " << i + 1 << std::endl;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

int main()
{
    cin_vec_int(n, vec);
    if (std::is_sorted(all(vec)) || std::is_sorted(rall(vec)))
    {
        std::cout << "Nothing to do here\n";
        return 0;
    }
    if (foo(vec, true) || foo(vec, !true))
    {
        return 0;
    }
    std::cout << "No hope\n";
    // cout_vec(vec);
}




