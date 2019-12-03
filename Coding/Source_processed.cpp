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

    int euler(int n)
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            ans += gcd(i, n) == 1;
        }
        return ans;
    }
    long long fast_euler(long long n)
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
// Test Khun

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<set>
#include<sstream>

using namespace std;
int time_to_int(const string& time)
{
    istringstream iss(time);
    int a, b;
    char ch;
    iss >> a >> ch >> b;
    return a * 100 + b;
}
string time_to_string(int time)
{
    return to_string(time / 100) + ":" + to_string(time % 100);
}
int plus_60_min(int time)
{
    int minimal_time = time;
    int a = minimal_time / 100;
    int b = minimal_time % 100;
    b += 60;
    a += b / 60;
    b %= 60;
    minimal_time = a * 100 + b;
    return minimal_time;
}
std::string flightPlan(std::vector<std::vector<std::string>> times, std::string source, std::string dest) {

    map<string, int> mapping;
    int index = 0;
    for (int i = 0; i < times.size(); ++i)
        for (int j = 0; j < 2; ++j)
            if (mapping.find(times[i][j]) == mapping.end())
                mapping[times[i][j]] = index++;
    struct Node
    {
        int to;
        int start;
        int end;
        Node() {}
        Node(int to, int start, int end) : to(to), start(start), end(end) {}
    };
    vector<vector<Node>> g(mapping.size());
    for (int i = 0; i < times.size(); ++i)
    {
        g[mapping[times[i][0]]].push_back
        ({ mapping[times[i][1]], time_to_int(times[i][2]), time_to_int(times[i][3]) });
    }
    const int Inf = 10000000;
    vector<int> dist(g.size(), Inf);
    int start = mapping[source];
    dist[start] = -60;
    set<pair<int, int>> s;
    s.insert({ 0, start });
    while (!s.empty())
    {
        int from = s.begin()->second;
        s.erase(s.begin());
        int minimal_time = plus_60_min(dist[from]);
        for (int i = 0; i < g[from].size(); ++i)
        {
            if (minimal_time <= g[from][i].start && g[from][i].end < dist[g[from][i].to])
            {
                s.erase({ dist[g[from][i].to], g[from][i].to });
                dist[g[from][i].to] = g[from][i].end;
                s.insert({ dist[g[from][i].to], g[from][i].to });
            }
        }
    }
    if (mapping.find(dest) == mapping.end())
        return "-1";
    if (dist[mapping[dest]] != Inf)
        return time_to_string(dist[mapping[dest]]);
    else
        return "-1";

}


int main()
{
    flightPlan({ {"Chicago", "Denver", "03:00", "06:00"},
        {"Chicago", "Denver", "03:30", "07:00" },
        {"Chicago", "Los Angeles", "01:00", "05:00"},
        {"Denver", "Austin", "06:30", "08:30"},
        {"Denver", "Austin", "07:30", "09:30"},
        {"Austin", "Denver", "06:30", "08:30"},
        {"Los Angeles", "Phoenix", "06:00", "07:00"},
        {"Los Angeles", "Phoenix", "05:30", "06:50"},
        {"Phoenix", "Austin", "08:00", "08:40"} }, "Chicago", "Austin");
}







