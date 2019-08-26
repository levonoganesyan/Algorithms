#include<Graph/Euler.h>
#include<algorithm>
namespace algo
{
    void Euler::dfs (const ConnectionList & graph, int vertex)
    {
        m_cycle.push_back(vertex);
        for (size_t i = 0; i < graph[vertex].size(); ++i)
        {
            int to = graph[vertex][i].to;
            if (m_used.find({ vertex, to }) != m_used.end())
            {
                continue;
            }
            m_used.insert({ vertex, to });
            m_used.insert({ to, vertex });
            dfs(graph, to);
        }
    }

    Euler::Euler(const Graph& graph)
        : Euler(graph.AsConnectionList())
    {
    }

    Euler::Euler(const ConnectionList & graph)
        : m_has_path(false)
        , m_has_cycle(false)
        , m_cycle(0)
    {
        std::vector<Graph::VertexType> odd_vertexes;
        for (size_t i = 0; i < graph.size(); i++)
        {
            if (graph[i].size() & 1)
            {
                if (odd_vertexes.size() == 2)
                {
                    return;
                }
                odd_vertexes.push_back(i);
            }
        }
        m_has_path = true;
        if (!odd_vertexes.size())
        {
            m_has_cycle = true;
            odd_vertexes.push_back(0); // for determenistic
        }
        dfs(graph, odd_vertexes[0]);
        m_used.clear();
    }

    Euler::Euler
    (const ConnectionMatrix & graph)
        : Euler(Graph::CM2CL(graph))
    {
    }

    Euler::Euler
    (const ListOfEdges & graph)
        : Euler(Graph::LOE2CL(graph))
    {
    }

    bool Euler::HasCycle() const
    {
        return m_has_cycle;
    }
    bool Euler::HasPath() const
    {
        return m_has_path;
    }

    std::vector<Euler::VertexType> Euler::GetCycle() const
    {
        return m_cycle;
    }


}

