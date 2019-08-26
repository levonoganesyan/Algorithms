#include "Graph\LCA.h"
namespace algo
{

    void LCA::dfs(const ConnectionList& graph, int vertex, int prev)
    {
        m_time_in[vertex] = ++m_timer;
        m_up[vertex][0] = prev;
        for (int i = 1; i < m_up[vertex].size(); ++i)
        {
            m_up[vertex][i] = m_up[m_up[vertex][i - 1]][i - 1];
        }
        for (int i = 0; i < graph[vertex].size(); ++i)
        {
            int to = graph[vertex][i].to;
            if (to != prev)
            {
                dfs(graph, to, vertex);
            }
        }
        m_time_out[vertex] = ++m_timer;
    }

    bool LCA::upper(int a, int b) const
    {
        return m_time_in[a] <= m_time_in[b] && 
                m_time_out[a] >= m_time_out[b];
    }

    int LCA::greater_power_of_2(int n)
    {
        int power = 1;
        while ((1 << power) <= n)
        {
            ++power;
        }
        return power + 1;
    }

    LCA::LCA(const Graph& graph)
        : LCA(graph.AsConnectionList())
    {
    }

    LCA::LCA(const ConnectionList& graph)
        : m_up(graph.size(),std::vector<int>(greater_power_of_2(graph.size())))
        , m_time_in(graph.size())
        , m_time_out(graph.size())
        , m_timer(0)
    {
        dfs(graph);
    }

    LCA::LCA(const ConnectionMatrix& graph)
        : LCA(Graph::CM2CL(graph))
    {
    }

    LCA::LCA(const ListOfEdges& graph)
        : LCA(Graph::LOE2CL(graph))
    {
    }
    int LCA::Get(int a, int b) const
    {
        if (upper(a, b))
            return a;
        if (upper(b, a))
            return b;
        for (int i = m_up[a].size() - 1; i >= 0; --i)
        {
            if (!upper(m_up[a][i], b))
            {
                a = m_up[a][i];
            }
        }
        return m_up[a][0];
    }
}

