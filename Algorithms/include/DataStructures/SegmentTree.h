#pragma once
#include<vector>
#include<functional>
namespace algo
{
	template<typename T>
	class SegmentTree
	{
		std::vector<T> m_vec;
		std::vector<T> m_tree;
		std::function<T(T, T)> m_tree_logic;
		int m_neutral_element;

		void build_tree(int v, int l, int r);
		void update(int i, T a, int v, int l, int r);
		int query(int a, int b, int v, int l, int r) const;
		static int left(int v);
		static int right(int v);
		static int mid(int l, int r);
	public:
		SegmentTree(const std::vector<T>& vec, 
					const std::function<T(T, T)> tree_logic,
					int neutral_element);
		
		void build_tree();
		void update(int i, T a);
		int query(int a, int b) const;
		int size() const;
	};
}


namespace algo
{
	template<typename T>
	void SegmentTree<T>::build_tree(int v, int l, int r)
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
	void SegmentTree<T>::update(int i, T a, int v, int l, int r)
	{
		if (l == r)
		{
			m_tree[v] = a;
			m_vec[i] = a;
		}
		else
		{
			int m = mid(l, r);
			if (i <= m)
			{
				build_tree(left(v), l, m);
			}
			else
			{
				build_tree(right(v), m + 1, r);
			}
			m_tree[v] = m_tree_logic(m_tree[left(v)], m_tree[right(v)]);
		}
	}

	template<typename T>
	int SegmentTree<T>::query(int a, int b, int v, int l, int r) const
	{
		if (a > b)
		{
			return m_neutral_element;
		}
		if (a == l && b == r)
		{
			return m_tree[v];
		}
		else
		{
			int m = mid(l, r);
			int left_ans = query(a, std::min(m, b), left(v), l, m);
			int right_ans = query(std::max(a, m + 1), b, right(v), m + 1, r);
			return m_tree_logic(left_ans, right_ans);
		}
	}

	template<typename T>
	int SegmentTree<T>::left(int v)
	{
		return v << 1;
	}

	template<typename T>
	int SegmentTree<T>::right(int v)
	{
		return (v << 1) + 1;
	}

	template<typename T>
	int SegmentTree<T>::mid(int l, int r)
	{
		return (l + r) >> 1;
	}

	template<typename T>
	SegmentTree<T>::SegmentTree(const std::vector<T>& vec,
								const std::function<T(T, T)> tree_logic,
								int neutral_element)
		: m_vec(vec)
		, m_tree_logic(tree_logic)
		, m_neutral_element(neutral_element)
	{
		m_tree.resize(m_vec.size() << 2);
	}

	template<typename T>
	void SegmentTree<T>::build_tree()
	{
		build_tree(1, 0, m_vec.size() - 1);
	}

	template<typename T>
	void SegmentTree<T>::update(int i, T a)
	{
		update(i, a, 1, 0, m_vec.size() - 1);
	}

	template<typename T>
	int SegmentTree<T>::query(int a, int b) const
	{
		return query(a, b, 1, 0, m_vec.size() - 1);
	}
	template<typename T>
	int SegmentTree<T>::size() const
	{
		return m_vec.size();
	}
}
