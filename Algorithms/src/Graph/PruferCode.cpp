#include<Graph/PruferCode.h>
#include<set>
namespace algo
{
    PruferCode::PruferCode()
    {
    }
    std::vector<int> PruferCode::Encode(const Graph& graph)
    {
        auto connection_list = graph.AsConnectionList();
        std::vector<std::set<Graph::Edge>> g(connection_list.size());
        for (int i = 0; i < g.size(); ++i)
        {
            g[i].insert(connection_list[i].begin(), connection_list[i].end());
        }
        std::set<std::pair<int, int>> degs;
        for (int i = 0; i < g.size(); ++i)
        {
            degs.insert({ g[i].size(), i });
        }
        std::vector<int> used(g.size());
        std::vector<int> code;
        while (degs.size() > 2)
        {
            int from = degs.begin()->second;
            degs.erase(degs.begin());
            int to = g[from].begin()->to;
            g[from].erase(g[from].begin());
            g[to].erase(g[to].find(Graph::Edge{ to, from }));
            code.push_back(to);
            degs.erase(degs.find({ g[to].size() + 1, to }));
            degs.insert({ g[to].size(), to });
        }
        return code;
    }
    Graph PruferCode::Decode(const std::vector<int>& code)
    {
        return Graph(Graph::ConnectionList{ {} });
    }
}