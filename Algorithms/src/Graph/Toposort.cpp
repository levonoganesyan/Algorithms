#include<Graph/Toposort.h>
#include<Graph/CycleChecker.h>
#include<exception>
#include<algorithm>
namespace algo
{
    void Toposort::dfs(const ConnectionList & graph, int vertex)
    {
        m_used[vertex] = true;
        for (size_t i = 0; i < graph[vertex].size(); ++i)
        {
            int to = graph[vertex][i].to;
            if (!m_used[to])
            {
                dfs(graph, to);
            }
        }
        m_sorted_vertices.push_back(vertex);
    }

    Toposort::Toposort(const Graph& graph)
        : Toposort(graph.AsConnectionList())
    {
    }

    Toposort::Toposort(const ConnectionList & graph)
        : m_sorted_vertices(0)
        , m_used(graph.size())
    {
        /*CycleChecker cycle_checker(graph);
        if (cycle_checker.HasCycle())
        {
            throw std::logic_error("Graph must be acyclic for toposort");
        }*/
        for (size_t i = 0; i < m_used.size(); ++i)
        {
            if (!m_used[i])
            {
                dfs(graph, i);
            }
        }
        std::reverse(m_sorted_vertices.begin(), m_sorted_vertices.end());
    }

    Toposort::Toposort(const ConnectionMatrix & graph)
        : Toposort(Graph::CM2CL(graph))
    {
    }
    Toposort::Toposort(const ListOfEdges & graph)
        : Toposort(Graph::LOE2CL(graph))
    {
    }
    std::vector<Graph::VertexType> Toposort::GetNewVerticesIndices() const
    {
        return m_sorted_vertices;
    }
}



