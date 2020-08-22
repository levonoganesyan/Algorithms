#include"Graph/FordBellman.h"
#include"Defines.h"
namespace algo
{
    FordBellman::FordBellman(const Graph & graph, int start_vertex)
        : FordBellman(graph.AsListOfEdges(), start_vertex)
    {
    }
    FordBellman::FordBellman(const ConnectionList & graph, int start_vertex)
        : FordBellman(Graph::CL2LOE(graph), start_vertex)
    {
    }
    FordBellman::FordBellman(const ConnectionMatrix & graph, int start_vertex)
        : FordBellman(Graph::CM2LOE(graph), start_vertex)
    {
    }
    FordBellman::FordBellman(const ListOfEdges & graph, int start_vertex)
        : n(Graph::GetSize(graph))
        , m_parents(n, -1)
        , m_distance(n, Inf)
    {
        m_distance[start_vertex] = 0;
        bool any = true;
        while(any)
        {
            any = false;
            for (int j = 0; j < graph.size(); ++j)
            {
                if (m_distance[graph[j].from] < Inf)
                {
                    Graph::WeightType& to_dist = m_distance[graph[j].to];
                    Graph::WeightType from_dist = m_distance[graph[j].from] +
                                                    graph[j].weight;
                    if (to_dist > from_dist)
                    {
                        to_dist = from_dist;
                        m_parents[graph[j].to] = graph[j].from;
                        any = true;
                    }
                }
            }
        }
    }
    Graph::WeightType FordBellman::GetDistance(int to) const
    {
        return m_distance[to];
    }
    std::vector<Graph::WeightType> FordBellman::GetDistance() const
    {
        return m_distance;
    }
    std::vector<int> algo::FordBellman::GetPath(int to) const
    {
        if (m_distance[to] == Inf)
            return {};
        std::vector<int> path;
        if (m_parents[to] == -1)
        {
            return path;
        }
        for (int cur = to; cur != -1; cur = m_parents[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        return path;
    }
}