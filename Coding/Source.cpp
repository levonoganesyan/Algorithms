#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <Graph\Toposort.h>
#include <Sortings\Sorting.h>
#include <DataStructures\SegmentTree.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    algo::SegmentTree<int> tree(std::vector<int>(40000, 0), 
                                std::plus<int>(), 
                                0,
                                algo::SegmentTree<int>::UpdateType::Sum);
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        ans[tree.query(0, x)]++;
        tree.update(x, 1);
    }
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << endl;
    }
}



