#include <limits.h>
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <stack>
#include <cstdio>
#include <queue>
#include <numeric>
#include <deque>
#include <set>
#include <sstream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <ctime>

using namespace std;

long long ans = 0;

vector<int> merge(const vector<int>& v1, const vector<int>& v2)
{
    vector<int> v;
    int i = 0, j = 0;
    while (i < v1.size() && j < v2.size())
    {
        if (v1[i] <= v2[j])
        {
            v.push_back(v1[i++]);
        }
        else
        {
            v.push_back(v2[j++]);
            ans += v1.size() - i;
        }
    }
    while (i < v1.size())
    {
        v.push_back(v1[i++]);
    }
    while (j < v2.size())
    {
        v.push_back(v2[j++]);
    }
    return v;
}
void merge_sort(vector<int>& vec)
{
    if (vec.size() <= 1)
        return;
    int mid = vec.size() / 2;
    std::vector<int> f_v(vec.begin(), vec.begin() + mid);
    std::vector<int> s_v(vec.begin() + mid, vec.end());
    merge_sort(f_v);
    merge_sort(s_v);
    vec = merge(f_v, s_v);
}

int main()
{
    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();
    int t;
    cin >> t;
    while (t--)
    {
        ans = 0;
        int begin = clock();
        int n;
        cin >> n;
        vector<int> vec(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> vec[i];
        }
        merge_sort(vec);
        cout << ans << endl;
        int end = clock();
        cout << (end - begin) / 1000.0 << endl;
    }
}

