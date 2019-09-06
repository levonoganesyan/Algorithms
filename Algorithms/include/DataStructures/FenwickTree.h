#pragma once
#include<vector>
#include<functional>
namespace algo
{
    template<typename T>
    class FenwickTree
    {
    public:
    private:
        std::vector<T> m_vec;
        std::vector<T> m_tree;

        T query(int to) const;
    public:
        FenwickTree(const std::vector<T>& vec);

        void build_tree();
        void update(int pos, T elem);
        T query(int from, int to) const;
        int size() const;
    };
}


namespace algo
{
    template<typename T>
    inline FenwickTree<T>::FenwickTree(const std::vector<T>& vec)
        : m_vec(vec)
        , m_tree(m_vec.size())
    {
    }
    template<typename T>
    inline void algo::FenwickTree<T>::build_tree()
    {
        for (int i = 0; i < m_vec.size(); ++i)
        {
            update(i, m_vec[i]);
        }
    }
    template<typename T>
    inline void FenwickTree<T>::update(int pos, T elem)
    {
        for (; pos < m_vec.size(); pos |= pos + 1)
        {
            m_tree[pos] += elem;
        }
    }
    template<typename T>
    inline T FenwickTree<T>::query(int to) const
    {
        int sum = 0;
        for (; to >= 0; to = (to & (to + 1)) - 1)
        {
            sum += m_tree[to];
        }
        return sum;
    }
    template<typename T>
    inline T FenwickTree<T>::query(int from, int to) const
    {
        return query(to) - query(from - 1);
    }
    template<typename T>
    inline int FenwickTree<T>::size() const
    {
        return m_vec.size();
    }
}



