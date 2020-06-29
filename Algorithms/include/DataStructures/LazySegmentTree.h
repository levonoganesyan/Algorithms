#pragma once
#include<vector>
#include<functional>
#include<Math/Math.h>
namespace algo
{
    template<typename T>
    class LazySegmentTree
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
        std::vector<T> m_lazy_prop;
        std::function<T(T, T)> m_tree_logic;
        T m_neutral_element;
        UpdateType m_upd_type;

        void build_tree(int v, int l, int r);
        void update(int pos, T elem, int v, int l, int r);
        void update(int pos_l, int pos_r, T elem, int v, int l, int r);
        T query(int from, int to, int v, int l, int r);
        static int left(int v);
        static int right(int v);
        static int mid(int l, int r);
        void update_one(T& a, T b);
        T update_many(int v, int l, int r);
    public:
        LazySegmentTree(const std::vector<T>& vec,
                    const std::function<T(T, T)>& tree_logic,
                    T neutral_element,
                    UpdateType upd_type = UpdateType::Assign);
        
        void build_tree();
        void update(int pos, T elem);
        void update(int pos_l, int pos_r, T elem);
        T query(int from, int to);
        T query(int pos);
        int size() const;
    private:
        void push(int v)
        {
            if (m_lazy_prop[v] != m_neutral_element) {
                if (m_lazy_prop[left(v)] == m_neutral_element)
                    m_lazy_prop[left(v)] = m_lazy_prop[v];
                else
                    update_one(m_lazy_prop[left(v)], m_lazy_prop[v]);

                if (m_lazy_prop[right(v)] == m_neutral_element)
                    m_lazy_prop[right(v)] = m_lazy_prop[v];
                else
                    update_one(m_lazy_prop[right(v)], m_lazy_prop[v]);
                m_lazy_prop[v] = m_neutral_element;
            }
        }
    };
}


namespace algo
{
    template<typename T>
    inline void LazySegmentTree<T>::build_tree(int v, int l, int r)
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
    inline void LazySegmentTree<T>::update(int pos, T elem, int v, int l, int r)
    {
        if (l == r)
        {
            update_one(m_tree[v], elem);
            update_one(m_vec[pos], elem);
        }
        else
        {
            push(v);
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
    inline void LazySegmentTree<T>::update(int pos_l, int pos_r, T elem, int v, int l, int r)
    {
        if (pos_l > pos_r)
        {
            return;
        }
        if (pos_l == l && pos_r == r)
        {
            if (m_lazy_prop[v] == m_neutral_element)
                m_lazy_prop[v] = elem;
            else
                update_one(m_lazy_prop[v], elem);
        }
        else
        {
            push(v);
            int m = mid(l, r);
            update(pos_l, min(pos_r, m), elem, left(v), l, m);
            update(max(pos_l, m + 1), pos_r, elem, right(v), m + 1, r);
            T left_ans = update_many(left(v), l, m);
            T right_ans = update_many(right(v), m + 1, r);
            m_tree[v] = m_tree_logic(left_ans, right_ans);
        }
    }

    template<typename T>
    inline T LazySegmentTree<T>::query(int from, int to, int v, int l, int r)
    {
        if (from > to)
        {
            return m_neutral_element;
        }
        if (from == l && to == r)
        {
            if (m_lazy_prop[v] == m_neutral_element)
                return m_tree[v];
            return m_tree[v] + m_lazy_prop[v];
        }
        else
        {
            push(v);
            int m = mid(l, r);
            T left_ans = query(from, std::min(m, to), left(v), l, m);
            T right_ans = query(std::max(from, m+1), to, right(v), m + 1, r);
            m_tree[v] = m_tree_logic(update_many(left(v), l, m), 
                                    update_many(right(v), m + 1, r));
            return m_tree_logic(m_tree_logic(left_ans, right_ans), m_lazy_prop[v]);
        }
    }

    template<typename T>
    inline int LazySegmentTree<T>::left(int v)
    {
        return v << 1;
    }

    template<typename T>
    inline int LazySegmentTree<T>::right(int v)
    {
        return (v << 1) + 1;
    }

    template<typename T>
    inline int LazySegmentTree<T>::mid(int l, int r)
    {
        return (l + r) >> 1;
    }

    template<typename T>
    inline void LazySegmentTree<T>::update_one(T& a, T b)
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
    inline T LazySegmentTree<T>::update_many(int v, int l, int r)
    {
        return m_tree[v] + m_lazy_prop[v];
        /*T ans = m_tree[v] + m_lazy_prop[v];
        if (m_lazy_prop[v] != m_neutral_element)
        {
            if (m_upd_type == UpdateType::Assign)
            {
                update_one(ans, m_lazy_prop[v]);
            }
            else if (m_upd_type == UpdateType::Sum)
            {
                update_one(ans, m_lazy_prop[v] * (r - l + 1));
            }
            else if (m_upd_type == UpdateType::Product)
            {
                update_one(ans, bin_pow(m_lazy_prop[v], r - l + 1));
            }
        }
        return ans;*/
    }

    template<typename T>
    LazySegmentTree<T>::LazySegmentTree(const std::vector<T>& vec,
                                const std::function<T(T, T)>& tree_logic,
                                T neutral_element,
                                UpdateType upd_type)
        : m_vec(vec)
        , m_tree_logic(tree_logic)
        , m_neutral_element(neutral_element)
        , m_upd_type(upd_type)
    {
        m_tree.resize(m_vec.size() << 2);
        m_lazy_prop.resize(m_tree.size(), m_neutral_element);
        build_tree();
    }

    template<typename T>
    inline void LazySegmentTree<T>::build_tree()
    {
        build_tree(1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline void LazySegmentTree<T>::update(int pos, T elem)
    {
        update(pos, elem, 1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline void LazySegmentTree<T>::update(int pos_l, int pos_r, T elem)
    {
        return update(pos_l, pos_r, elem, 1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline T LazySegmentTree<T>::query(int from, int to)
    {
        return query(from, to, 1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline T LazySegmentTree<T>::query(int pos)
    {
        return query(pos, pos, 1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline int LazySegmentTree<T>::size() const
    {
        return m_vec.size();
    }
}





