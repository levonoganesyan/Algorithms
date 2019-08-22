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
		int m_neutral_element;
		UpdateType m_upd_type;

		void build_tree(int v, int l, int r);
		void update(int pos, T elem, int v, int l, int r);
		// void update(int pos_l, int pos_r, T elem, int v, int l, int r);
		int query(int from, int to, int v, int l, int r) const;
		static int left(int v);
		static int right(int v);
		static int mid(int l, int r);
		void update_one(int& a, int b);
	public:
		SegmentTree(const std::vector<T>& vec,
					const std::function<T(T, T)>& tree_logic,
					int neutral_element,
					UpdateType upd_type = UpdateType::Assign);
		
		void build_tree();
		void update(int pos, T elem);
		// void update(int pos_l, int pos_r, T elem);
		int query(int from, int to) const;
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
	inline void SegmentTree<T>::update(int pos_l, int pos_r, T elem, int v, int l, int r)
	{
		if (pos_l == l && pos_r == r)
		{
			m_lazy_prop = elem;
		}
	}*/

	template<typename T>
	inline int SegmentTree<T>::query(int from, int to, int v, int l, int r) const
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
			int left_ans = query(from, std::min(m, to), left(v), l, m);
			int right_ans = query(std::max(from, m + 1), to, right(v), m + 1, r);
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
								int neutral_element,
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
	inline int SegmentTree<T>::query(int from, int to) const
	{
		return query(from, to, 1, 0, m_vec.size() - 1);
	}
	template<typename T>
	inline int SegmentTree<T>::size() const
	{
		return m_vec.size();
	}
}





