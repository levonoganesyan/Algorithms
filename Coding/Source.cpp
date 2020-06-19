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
#include <DataStructures/SegmentTree.h>
#include <Math/Math.h>
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

