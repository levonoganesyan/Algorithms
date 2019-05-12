#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <sstream>
// #include <Graph\Toposort.h>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    if (b == 0)
    {
        cout << a * a * 100 + a * a + 2 * 10 * a * a << endl;
    }
    else if (b == 1)
    {
        cout << a * a * 10000 + a * a + 2 * 100 * a * a << endl;
    }
    else
    {
        string ans[] = { "00200",
                            "00800",
                            "01800",
                            "0320",
                            "0500",
                            "0720",
                            "0980",
                            "1280",
                            "1620" };
        int s = 1;
        if (s >= 4)
            s = 2;
        cout << a * a;
        for (int i = 0; i < b - 2; i++)
        {
            cout << 0;
        }
        cout << ans[a - 1];
        for (int i = 0; i < b - 2; i++)
        {
            cout << 0;
        }
        cout << a * a;
    }
}



