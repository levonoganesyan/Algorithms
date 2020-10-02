#pragma comment(linker, "/STACK:200000000")
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//struct Config
//{
//    static int battle_mages_count;
//    static int heal_mages_count;
//} config;
//
//class Mage
//{
//    // input values
//    double _max_value;
//    double _increasing_value;
//    double _decreasing_value;
//
//    // common values
//    double _max_hp;
//    double _velocity;
//
//    // changable values
//    double _current_value;
//    double _current_hp;
//    double _pos_x;
//    double _pos_y;
//
//public:
//    Mage(double max_hp, double velocity)
//        : _pos_x(0)
//        , _pos_y(0)
//        , _max_hp(max_hp)
//        , _velocity(velocity)
//        , _current_hp(max_hp)
//        , _current_value(0)
//
//        , _max_value(-1)
//        , _increasing_value(-1)
//        , _decreasing_value(-1)
//    {
//    }
//    void IncreaseValue(int msecs)
//    {
//        this->_current_value += this->_increasing_value * msecs / 1000.0;
//    }
//    double GetValue() const
//    {
//        this->_current_value;
//    }
//    void Move(int msecs)
//    {
//        // TODO
//    }
//    double GetDistance(double x, double y) const
//    {
//        return sqrt((x - this->_pos_x) * (x - this->_pos_x) + (y - this->_pos_x) * (y - this->_pos_y));
//    }
//    double GetVelocity() const
//    {
//        return this->_velocity;
//    }
//    friend istream& operator>>(istream& is, Mage& mage);
//    virtual void DoAction() = 0;
//};
//
//istream& operator>>(istream& is, Mage& mage)
//{
//    is >> mage._max_value >> mage._increasing_value >> mage._decreasing_value;
//}
//
//
//class DamageMage : public Mage
//{
//public:
//    DamageMage(double max_hp, double velocity) : Mage(max_hp, velocity) {}
//    virtual void DoAction()
//    {
//        // TODO
//    }
//};
//
//
//class HealingMage : public Mage
//{
//public:
//    HealingMage(double max_hp, double velocity) : Mage(max_hp, velocity) {}
//    virtual void DoAction()
//    {
//        // TODO
//    }
//};
//
//class DragonAttack
//{
//    double _power;
//    double _duration;
//    virtual void input(istream& is) = 0;
//public:
//    friend istream& operator>>(istream& is, DragonAttack& attack);
//};
//istream& operator>>(istream& is, DragonAttack& attack)
//{
//    attack.input(is);
//}
//
//class BreathAttack : public DragonAttack
//{
//    vector<double> _pos_xs;
//    vector<double> _pos_ys;
//    virtual void input(istream& is)
//    {
//        int size = config.battle_mages_count + config.heal_mages_count;
//        _pos_xs.resize(size);
//        _pos_ys.resize(size);
//        for (int i = 0; i < size; ++i)
//        {
//            is >> _pos_xs[i] >> _pos_ys[i];
//        }
//    }
//};
//
//class StormAttack : public DragonAttack
//{
//    double _pos_x;
//    double _pos_y;
//    virtual void input(istream& is) = 0;
//};
//
//class TailAttack : public DragonAttack
//{
//
//};
//
//class Game
//{
//
//};

#pragma once
#include<vector>
#include<string>
#include<type_traits>
namespace algo
{
    class StringHashing
    {
    public:
        typedef unsigned long long HashType;
    private:
        const int m_prime = 331;
    private:
        HashType m_mod;
        std::string m_str;
        std::vector<HashType> m_hashes;
        std::vector<HashType> m_primes;
    private:
        void build_hash();
    public:
        explicit StringHashing(const std::string& str, 
                      HashType mod = LLONG_MAX);

        HashType Get() const;
        HashType Get(int i, int j) const;
        std::size_t Size() const;

    };
}

namespace algo
{
    void StringHashing::build_hash()
    {
        m_primes[0] = 1;
        for (int i = 0; i < m_str.size(); ++i)
        {
            m_hashes[i + 1] = m_hashes[i] * m_prime + m_str[i];
            m_hashes[i + 1] %= m_mod;
            m_primes[i + 1] = m_primes[i] * m_prime;
            m_primes[i + 1] %= m_mod;
        }
    }
    StringHashing::StringHashing(const std::string& str, StringHashing::HashType mod)
        : m_str(str)
        , m_hashes(str.size() + 1)
        , m_primes(str.size() + 1)
        , m_mod(mod)
    {
        build_hash();
    }
    StringHashing::HashType StringHashing::Get() const
    {
        return Get(0, m_str.size() - 1);
    }
    StringHashing::HashType StringHashing::Get(int i, int j) const
    {
        HashType hash = m_hashes[j + 1];
        hash -= (m_hashes[i] * m_primes[j - i + 1]) % m_mod;
        if (hash < 0)
            hash += m_mod;
        return hash;
    }
    std::size_t StringHashing::Size() const
    {
        return m_str.size();
    }
}
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





#include<unordered_map>

int segment_tree_update(int a, int b)
{
    if (a * 1ll * b > 1e5)
    {
        return 0;
    }
    return a * b;
}

void print(int a)
{
    // cerr << "----------------------------------" <<  a << " ";
    if (a < 10)
        cout << "Slideshow";
    else if (a < 60)
        cout << "So-so";
    else
        cout << "Perfect";
    cout << endl;
}

void check(int mult, int t, int h, int w)
{
    if (mult == 0)
    {
        print(0);
    }
    else
    {
        print(t / (w * 1ll * h * mult));
    }
}

int main()
{
    unordered_map<algo::StringHashing::HashType, int> indices;
    int n;
    cin >> n;
    vector<int> mults(n);
    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        indices[algo::StringHashing(s).Get()] = i;
        cin >> mults[i];
    }
    algo::SegmentTree<int> tree(mults, segment_tree_update, 1, algo::SegmentTree<int>::UpdateType::Assign);

    int h, w, t;
    cin >> h >> w >> t;

    check(tree.query(0, n - 1), t, h, w);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        string s;
        cin >> s;
        if (s == "On")
        {
            string t;
            cin >> t;
            int index = indices[algo::StringHashing(t).Get()];
            tree.update(index, mults[index]);
        }
        else if (s == "Off")
        {
            string t;
            cin >> t;
            int index = indices[algo::StringHashing(t).Get()];
            tree.update(index, 1);
        }
        else
        {
            cin >> h >> w;
        }
        check(tree.query(0, n - 1), t, h, w);
    }
}
