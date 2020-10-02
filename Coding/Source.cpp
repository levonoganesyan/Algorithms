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

#include<Strings/StringHashing.h>
#include<DataStructures/SegmentTree.h>
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