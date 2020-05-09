#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <Math/Math.h>
using namespace std;

// Test z-function
// Test Khun

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<set>
#include<sstream>
#include<Graph/Graph.h>
#include<Graph/Euler.h>

using namespace std;

int main()
{
    algo::Graph::ListOfEdges loe;
    loe.push_back({ 0, 1 });
    loe.push_back({ 0, 2 });
    loe.push_back({ 0, 3 });
    loe.push_back({ 0, 5 });
    loe.push_back({ 1, 2 });
    loe.push_back({ 1, 3 });
    loe.push_back({ 1, 4 });
    loe.push_back({ 2, 3 });
    loe.push_back({ 2, 5 });
    loe.push_back({ 3, 4 });
    loe = algo::Graph::MakeUndirected(loe);
    algo::Graph g(loe);

    algo::Euler euler(g);

    std::cout << euler.HasCycle() << endl;
    vector<algo::Graph::VertexType> cycle = euler.GetCycle();
    for (int i = 0; i < cycle.size(); ++i)
    {
        cout << cycle[i] << " ";
    }

}







