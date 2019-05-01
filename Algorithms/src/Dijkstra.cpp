#include"Dijkstra.h"
#include"Defines.h"
algo::Dijkstra::ConnectionList
    algo::Dijkstra::ListOfEdgesToConnectionList
        (const algo::Dijkstra::ListOfEdges & list_of_edges)
{
    ConnectionList connection_list;
    for (const auto& edge : list_of_edges)
    {
        int from = edge.from;
        int to = edge.to;
        connection_list.resize(algo::max(from, to,
                                        (int)connection_list.size()));
        connection_list[from].push_back({ from, to, edge.weight });
        connection_list[to].push_back({ to, from, edge.weight });
    }
    return connection_list;
}


algo::Dijkstra::Dijkstra(const algo::Dijkstra::ConnectionList & graph,
                        int start_vertex,
                        algo::ConnectionListTag)
    : m_start_vertex(start_vertex)
{
    assert(start_vertex < (int)graph.size());

    m_distance.resize(graph.size(), Inf);
    m_distance[start_vertex] = 0;
    m_parents.resize(graph.size());
    std::set<std::pair<Graph::WeightType, int>> queue;
    queue.emplace(0, start_vertex);
    while (!queue.empty())
    {
        int from = queue.begin()->second;
        queue.erase(queue.begin());

        for (size_t i = 0; i < graph[from].size(); ++i)
        {
            int to = graph[from][i].to;
            int weight = graph[from][i].weight;

            if (m_distance[from] + weight < m_distance[to])
            {
                queue.erase({ m_distance[to], to });
                m_distance[to] = m_distance[from] + weight;
                m_parents[to] = from;
                queue.insert({ m_distance[to], to });
            }
        }
    }
}

algo::Dijkstra::Dijkstra(const algo::Dijkstra::ConnectionMatrix& graph,
                        int start_vertex,
                        algo::ConnectionMatrixTag)
    : m_start_vertex(start_vertex)
{
    m_distance.resize(graph.size(), Inf);
    // TODO
}

algo::Dijkstra::Dijkstra(const algo::Dijkstra::ListOfEdges& graph,
                        int start_vertex,
                        algo::ListOfEdgesTag)
    : Dijkstra(ListOfEdgesToConnectionList(graph), 
                start_vertex, 
                algo::ConnectionListTag())
{
}

int algo::Dijkstra::GetDistance(int to)
{
    assert(to < (int)m_distance.size());
    return m_distance[to];
}


std::vector<int> algo::Dijkstra::GetPath(int to)
{
    assert(to < (int)m_distance.size());
    std::vector<int> path;
    for (int v = to; v != m_start_vertex; v = m_parents[v])
    {
        path.push_back(to);
    }
    path.push_back(m_start_vertex);
    std::reverse(all(path));
    return path;
}


