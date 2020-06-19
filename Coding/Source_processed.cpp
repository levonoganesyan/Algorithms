#include <limits.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <queue>
#include <sstream>
#include <unordered_map>
#pragma once
#include<vector>
#include<functional>
namespace algo
{
    template<typename T>
    class SegmentTree
    {
    public:
        static T min(T a, T b)
        {
            return a < b ? a : b;
        }
        static T max(T a, T b)
        {
            return a > b ? a : b;
        }
        enum class UpdateType
        {
            Assign,
            Sum,
            Product
        };
    private:
        std::vector<T> m_vec;
        std::vector<T> m_tree;
        std::vector<T> m_lazy_prop;
        std::function<T(T, T)> m_tree_logic;
        T m_neutral_element;
        UpdateType m_upd_type;

        void build_tree(int v, int l, int r);
        void update(int pos, T elem, int v, int l, int r);
        // void update(int pos_l, int pos_r, T elem, int v, int l, int r);
        T query(int from, int to, int v, int l, int r) const;
        static int left(int v);
        static int right(int v);
        static int mid(int l, int r);
        void update_one(int& a, int b);
    public:
        SegmentTree(const std::vector<T>& vec,
                    const std::function<T(T, T)>& tree_logic,
                    T neutral_element,
                    UpdateType upd_type = UpdateType::Assign);
        
        void build_tree();
        void update(int pos, T elem);
        // void update(int pos_l, int pos_r, T elem);
        T query(int from, int to) const;
        int size() const;
    };
}


namespace algo
{
    template<typename T>
    inline void SegmentTree<T>::build_tree(int v, int l, int r)
    {
        if (l == r)
        {
            m_tree[v] = m_vec[l];
        }
        else
        {
            int m = mid(l, r);
            build_tree(left(v), l, m);
            build_tree(right(v), m + 1, r);
            m_tree[v] = m_tree_logic(m_tree[left(v)], m_tree[right(v)]);
        }
    }

    template<typename T>
    inline void SegmentTree<T>::update(int pos, T elem, int v, int l, int r)
    {
        if (l == r)
        {
            update_one(m_tree[v], elem);
            update_one(m_vec[pos], elem);
        }
        else
        {
            int m = mid(l, r);
            if (pos <= m)
            {
                update(pos, elem, left(v), l, m);
            }
            else
            {
                update(pos, elem, right(v), m + 1, r);
            }
            m_tree[v] = m_tree_logic(m_tree[left(v)], m_tree[right(v)]);
        }
    }

    /*template<typename T>
    inline void SegmentTree<T>::update(int pos_l, 
                                        int pos_r, 
                                        T elem, 
                                        int v, 
                                        int l, 
                                        int r)
    {
        if (pos_l == l && pos_r == r)
        {
            m_lazy_prop = elem;
        }
    }*/

    template<typename T>
    inline T SegmentTree<T>::query(int from, int to, int v, int l, int r) const
    {
        if (from > to)
        {
            return m_neutral_element;
        }
        if (from == l && to == r)
        {
            return m_tree[v];
        }
        else
        {
            int m = mid(l, r);
            T left_ans = query(from, std::min(m, to), left(v), l, m);
            T right_ans = query(std::max(from, m+1), to, right(v), m + 1, r);
            return m_tree_logic(left_ans, right_ans);
        }
    }

    template<typename T>
    inline int SegmentTree<T>::left(int v)
    {
        return v << 1;
    }

    template<typename T>
    inline int SegmentTree<T>::right(int v)
    {
        return (v << 1) + 1;
    }

    template<typename T>
    inline int SegmentTree<T>::mid(int l, int r)
    {
        return (l + r) >> 1;
    }

    template<typename T>
    inline void SegmentTree<T>::update_one(int& a, int b)
    {
        switch (m_upd_type)
        {
        case UpdateType::Assign:
            a = b;
            break;
        case UpdateType::Sum:
            a += b;
            break;
        case UpdateType::Product:
            a *= b;
            break;
        default:
            break;
        }
    }

    template<typename T>
    SegmentTree<T>::SegmentTree(const std::vector<T>& vec,
                                const std::function<T(T, T)>& tree_logic,
                                T neutral_element,
                                UpdateType upd_type)
        : m_vec(vec)
        , m_tree_logic(tree_logic)
        , m_neutral_element(neutral_element)
        , m_upd_type(upd_type)
    {
        m_tree.resize(m_vec.size() << 2);
    }

    template<typename T>
    inline void SegmentTree<T>::build_tree()
    {
        build_tree(1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline void SegmentTree<T>::update(int pos, T elem)
    {
        update(pos, elem, 1, 0, m_vec.size() - 1);
    }

    /*template<typename T>
    inline void SegmentTree<T>::update(int pos_l, int pos_r, T elem)
    {
        if (m_lazy_prop.empty())
        {
            m_lazy_prop.resize(m_tree.size());
        }
        update(pos_l, pos_r, elem, 1, 0, m_vec.size() - 1);
    }*/

    template<typename T>
    inline T SegmentTree<T>::query(int from, int to) const
    {
        return query(from, to, 1, 0, m_vec.size() - 1);
    }
    template<typename T>
    inline int SegmentTree<T>::size() const
    {
        return m_vec.size();
    }
}





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
        return b ? gcd(b, a % b) : a;
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

long long update(long long a, long long b)
{
    if (a == -1)
        return b;
    if (b == -1)
        return a;
    return algo::gcd(a, b);
}

long long mygcd(long long a, long long b)
{
    return b ? mygcd(b, a % b) : a;
}


pair<long long, long long> minimum(pair<long long, long long> a, pair<long long, long long> b)
{
    if (a.first == b.first)
    {
        return make_pair(a.first, a.second + b.second);
    }
    else
    {
        if (a.first < b.first)
            return a;
        else
            return b;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<long long> vec(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> vec[i];
    }
    vector<pair<long long, long long>> vec1(n);
    for (int i = 0; i < n; ++i)
    {
        vec1[i] = { vec[i], 1 };
    }
    algo::SegmentTree<long long> tree_gcd(vec, mygcd, 0);
    algo::SegmentTree<pair<long long, long long>> tree_min(vec1, minimum, { 2000000000000ll, 0 });
    tree_gcd.build_tree();
    tree_min.build_tree();
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int a, b;
        cin >> a >> b;

        a--;
        b--;
        int ans = b - a;
        auto ans_gcd = tree_gcd.query(a, b);
        // cout << ans_gcd << " ";
        auto ans_min = tree_min.query(a, b);
        // cout << ans_min.first << " " << ans_min.second << " ";
        if (ans_min.first == ans_gcd)
        {
            ans -= ans_min.second;
        }
        cout << ans + 1 << endl;
    }

}

