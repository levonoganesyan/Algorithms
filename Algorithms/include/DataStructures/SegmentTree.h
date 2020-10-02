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
        static T sum(T a, T b)
        {
            return a + b;
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
        std::function<T(T, T)> m_tree_logic;
        T m_neutral_element;
        UpdateType m_upd_type;

        void build_tree(int v, int l, int r);
        void update(int pos, T elem, int v, int l, int r);
        T query(int from, int to, int v, int l, int r) const;
        static int left(int v);
        static int right(int v);
        static int mid(int l, int r);
        void update_one(T& a, T b);
    public:
        SegmentTree(const std::vector<T>& vec,
                    const std::function<T(T, T)>& tree_logic,
                    T neutral_element,
                    UpdateType upd_type = UpdateType::Assign);
        
        void build_tree();
        void update(int pos, T elem);
        T query(int from, int to) const;
        T query(int pos) const;
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
    inline void SegmentTree<T>::update_one(T& a, T b)
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
        if (m_vec.size() == 0)
            return;
        m_tree.resize(m_vec.size() << 2);
        build_tree();
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

    template<typename T>
    inline T SegmentTree<T>::query(int from, int to) const
    {
        return query(from, to, 1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline T SegmentTree<T>::query(int pos) const
    {
        return query(pos, pos, 1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline int SegmentTree<T>::size() const
    {
        return m_vec.size();
    }
}





