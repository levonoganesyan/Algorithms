#pragma comment(linker, "/STACK:500000000")
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<unordered_set>
#include<set>
#include<iomanip>
#include<queue>
#include<cmath>
#include<Graph/Dijkstra.h>
using namespace std;

map<pair<int, int>, int> cti;
int curr = 0;

algo::Graph::ConnectionList graph;

void matrix_to_graph(const vector<vector<char>>& matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (matrix[i][j] == '#')
                continue;
            if (cti.find({ i, j }) == cti.end())
            {
                cti[{i, j}] = curr++;
            }
            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    if (!l && !k)
                        continue;
                    int x = i + k;
                    int y = j + l;
                    
                    if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size())
                    {
                        if (cti.find({ x, y }) == cti.end())
                        {
                            cti[{x, y}] = curr++;
                        }
                        if (matrix[x][y] != '#')
                        {
                            algo::Graph::Edge e;
                            e.from = cti[{i, j}];
                            e.to   = cti[{x, y}];
                            e.weight = (k == 0 || l == 0) ? 1 : sqrt(2.0);
                            graph[cti[{i, j}]].push_back(e);
                            swap(e.to, e.from);
                            graph[cti[{x, y}]].push_back(e);
                        }
                    }
                }
            }
        }
    }
}

int main() 
{
    const int Inf = 1000000000;
    int n, m;
    cin >> n >> m;
    graph.resize(n * m);
    int k;
    cin >> k;
    double v;
    cin >> v;
    swap(n, m);
    vector<vector<char>> matrix(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> matrix[i][j];

    matrix_to_graph(matrix);

    int x, y;
    cin >> x >> y;
    --x;
    --y;
    swap(x, y);
    double dist = 0;
    for (int i = 0; i < k; ++i)
    {
        algo::Dijkstra dijkstra(graph, cti[{x, y}]);
        int a, b;
        cin >> a >> b;
        --a, --b;
        swap(a, b);
        if (dijkstra.GetDistance(cti[{a, b}]) != algo::Inf)
        {
            dist += dijkstra.GetDistance(cti[{a, b}]);
            x = a;
            y = b;
        }
    }

    cout << fixed << setprecision(2) << dist / v;

}