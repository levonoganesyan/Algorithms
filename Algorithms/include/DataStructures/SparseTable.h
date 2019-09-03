#pragma once
#include<vector>

namespace algo
{
    template<typename T>
    class SparseTable
    {
        std::vector<T> m_arr;
        std::vector<int> m_logs;
        std::vector<std::vector<int>> m_table;


        void compute_logs();
        void build_sparse_table();
    public:
        SparseTable(const std::vector<T>& arr);
        T get_min(int a, int b) const;
    };
}




namespace algo
{
    template<typename T>
    inline void SparseTable<T>::compute_logs()
    {
        m_logs[1] = 0;
        for (int i = 2; i < m_logs.size(); ++i)
        {
            m_logs[i] = m_logs[i >> 1] + 1;
        }
    }
    template<typename T>
    inline void SparseTable<T>::build_sparse_table()
    {
        m_table[0] = a;

        for (int i = 1; i < m_logs[m_arr.size()]; ++i)
        {
            int cur_length = 1 << i;
            for (int j = 0; j + cur_length <= arr.size(); ++j)
            {
                m_table[i][j] = std::min(m_table[i - 1][j], m_table[i - 1][j + (cur_length >> 1)];
            }
        }
    }
    template<typename T>
    inline SparseTable<T>::SparseTable(const std::vector<T>& arr)
        : m_arr(arr)
        , m_logs(arr.size() + 1)
        , table(log2(arr.size()) + 1, std::vector<int>(arr.size()))
    {
    }
    template<typename T>
    inline T SparseTable<T>::get_min(int l, int r) const
    {
        int lo = m_logs[r - l + 1];
        return min(m_table[lo][l], m_table[lo][r - (1 << lo) + 1]);
    }
}