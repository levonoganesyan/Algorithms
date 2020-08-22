#include"Graph/Dijkstra.h"
#include"Defines.h"
namespace algo
{
    Dijkstra::Dijkstra(const Graph& graph, int start_vertex)
        : Dijkstra(graph.AsConnectionList(), start_vertex)
    {
    }
    Dijkstra::Dijkstra
        (const Dijkstra::ConnectionList & graph,
         int start_vertex)
            : m_start_vertex(start_vertex)
    {
        assert(start_vertex < (int)graph.size());

        m_distance.resize(graph.size(), Inf);
        m_distance[start_vertex] = 0;
        m_parents.resize(graph.size());
        for (size_t i = 0; i < m_parents.size(); ++i)
        {
            m_parents[i] = (int)i;
        }
        std::set<std::pair<Graph::WeightType, int>> queue;
        queue.emplace(0, start_vertex);
        while (!queue.empty())
        {
            int from = queue.begin()->second;
            queue.erase(queue.begin());

            for (size_t i = 0; i < graph[from].size(); ++i)
            {
                int to = graph[from][i].to;
                Graph::WeightType weight = graph[from][i].weight;

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

    Dijkstra::Dijkstra
        (const Dijkstra::ConnectionMatrix& graph,
         int start_vertex)
        : m_start_vertex(start_vertex)
    {
        m_distance.resize(graph.size(), Inf);
        m_distance[start_vertex] = 0;
        m_parents.resize(graph.size());
        for (size_t i = 0; i < m_parents.size(); ++i)
        {
            m_parents[i] = (int)i;
        }
        std::vector<char> used(graph.size());
        for (size_t i = 0; i < graph.size(); ++i)
        {
            size_t v = 0;
            bool first_choose = true;
            for (size_t j = 0; j < graph[i].size(); ++j)
            {
                if (!used[j] && (first_choose ||
                    m_distance[j] < m_distance[v]))
                {
                    v = j;
                    first_choose = false;
                }
            }
            if (m_distance[v] == Inf)
                break;

            used[v] = true;

            for (size_t j = 0; j < graph[i].size(); ++i)
            {
                size_t to = j;
                Graph::WeightType weight = graph[i][j];
                if (m_distance[to] > m_distance[v] + weight)
                {
                    m_distance[to] = m_distance[v] + weight;
                    m_parents[to] = (int)v;
                }
            }
        }
    }

    Dijkstra::Dijkstra
        (const Dijkstra::ListOfEdges& graph,
         int start_vertex) : Dijkstra(Graph::LOE2CL(graph), start_vertex)
    {
    }

    Graph::WeightType
        Dijkstra::GetDistance
            (int to) const
    {
        assert(to < (int)m_distance.size());
        return m_distance[to];
    }

    std::vector<Graph::WeightType>
        Dijkstra::GetDistance
            () const
    {
        return m_distance;
    }


    std::vector<int>
        Dijkstra::GetPath
            (int to) const
    {
        assert(to < (int)m_parents.size());
        std::vector<int> path;
        if (to == m_parents[to])
        {
            return path;
        }
        for (int v = to; v != m_start_vertex; v = m_parents[v])
        {
            path.push_back(v);
        }
        path.push_back(m_start_vertex);
        std::reverse(all(path));
        return path;
    }

}


