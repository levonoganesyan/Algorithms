#include<Graph/Bridges.h>

namespace algo
{
    void Bridges::dfs(const ConnectionList& graph, int v, int p)
    {
        m_used[v] = true;
        m_time_in[v] = m_f_up[v] = ++m_timer;

        for (int i = 0; i < graph[v].size(); ++i)
        {
            int to = graph[v][i].to;
            if (to == p)
            {
                continue;
            }
            if (m_used[to])
            {
                m_f_up[v] = min(m_f_up[v], m_time_in[to]);
            }
            else
            {
                dfs(graph, to, v);
                m_f_up[v] = min(m_f_up[v], m_f_up[to]);
                if (m_f_up[to] > m_time_in[v])
                {
                    m_bridges.push_back({v, to});
                }
            }
        }
    }

    Bridges::Bridges(const Graph& graph)
        : Bridges(graph.AsConnectionList())
    {
    }

    Bridges::Bridges(const ConnectionList& graph)
        : m_timer(0)
        , m_time_in(graph.size())
        , m_time_out(graph.size())
        , m_used(graph.size())
        , m_f_up(graph.size())
    {
        for (int i = 0; i < m_used.size(); ++i)
        {
            if (!m_used[i])
            {
                dfs(graph, i);
            }
            std::sort(m_bridges.begin(), m_bridges.end());
            auto iter = std::unique(m_bridges.begin(), m_bridges.end());
            m_bridges.erase(iter, m_bridges.end());
        }
    }

    Bridges::Bridges(const ConnectionMatrix& graph)
        : Bridges(Graph::CM2CL(graph))
    {
    }

    Bridges::Bridges(const ListOfEdges& graph)
        : Bridges(Graph::LOE2CL(graph))
    {
    }
    std::vector<Bridges::Edge> Bridges::Get() const
    {
        return m_bridges;
    }
}