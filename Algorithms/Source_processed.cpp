#include <iostream>
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

#pragma once
#include<algorithm>
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






bool foo(std::vector<int> vec, bool b)
{
    auto original = vec;
    if(b)   
        std::sort(all(vec));
    else
        std::sort(rall(vec));

    int f = -1;
    for (int i = 0; i < vec.size(); ++i)
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




