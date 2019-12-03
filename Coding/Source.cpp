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

using namespace std;
int time_to_int(const string& time)
{
    istringstream iss(time);
    int a, b;
    char ch;
    iss >> a >> ch >> b;
    return a * 100 + b;
}
string time_to_string(int time)
{
    return to_string(time / 100) + ":" + to_string(time % 100);
}
int plus_60_min(int time)
{
    int minimal_time = time;
    int a = minimal_time / 100;
    int b = minimal_time % 100;
    b += 60;
    a += b / 60;
    b %= 60;
    minimal_time = a * 100 + b;
    return minimal_time;
}
std::string flightPlan(std::vector<std::vector<std::string>> times, std::string source, std::string dest) {

    map<string, int> mapping;
    int index = 0;
    for (int i = 0; i < times.size(); ++i)
        for (int j = 0; j < 2; ++j)
            if (mapping.find(times[i][j]) == mapping.end())
                mapping[times[i][j]] = index++;
    struct Node
    {
        int to;
        int start;
        int end;
        Node() {}
        Node(int to, int start, int end) : to(to), start(start), end(end) {}
    };
    vector<vector<Node>> g(mapping.size());
    for (int i = 0; i < times.size(); ++i)
    {
        g[mapping[times[i][0]]].push_back
        ({ mapping[times[i][1]], time_to_int(times[i][2]), time_to_int(times[i][3]) });
    }
    const int Inf = 10000000;
    vector<int> dist(g.size(), Inf);
    int start = mapping[source];
    dist[start] = -60;
    set<pair<int, int>> s;
    s.insert({ 0, start });
    while (!s.empty())
    {
        int from = s.begin()->second;
        s.erase(s.begin());
        int minimal_time = plus_60_min(dist[from]);
        for (int i = 0; i < g[from].size(); ++i)
        {
            if (minimal_time <= g[from][i].start && g[from][i].end < dist[g[from][i].to])
            {
                s.erase({ dist[g[from][i].to], g[from][i].to });
                dist[g[from][i].to] = g[from][i].end;
                s.insert({ dist[g[from][i].to], g[from][i].to });
            }
        }
    }
    if (mapping.find(dest) == mapping.end())
        return "-1";
    if (dist[mapping[dest]] != Inf)
        return time_to_string(dist[mapping[dest]]);
    else
        return "-1";

}


int main()
{
    flightPlan({ {"Chicago", "Denver", "03:00", "06:00"},
        {"Chicago", "Denver", "03:30", "07:00" },
        {"Chicago", "Los Angeles", "01:00", "05:00"},
        {"Denver", "Austin", "06:30", "08:30"},
        {"Denver", "Austin", "07:30", "09:30"},
        {"Austin", "Denver", "06:30", "08:30"},
        {"Los Angeles", "Phoenix", "06:00", "07:00"},
        {"Los Angeles", "Phoenix", "05:30", "06:50"},
        {"Phoenix", "Austin", "08:00", "08:40"} }, "Chicago", "Austin");
}







