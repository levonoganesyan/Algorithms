#include<Graph/CycleChecker.h>
#include<algorithm>
#include "..\..\include\Graph\CycleChecker.h"
namespace algo
{
    bool
        CycleChecker::dfs
            (const ConnectionList & graph, int vertex)
    {
        m_vertices_state[vertex] = VertexState::Visited;
        for (size_t i = 0; i < graph[vertex].size(); ++i)
        {
            int to = graph[vertex][i].to;
            if (m_vertices_state[to] == VertexState::NotVisited)
            {
                m_parents[to] = vertex;
                if (dfs(graph, to))
                {
                    return true;
                }
            }
            else if (m_vertices_state[to] == VertexState::Visited)
            {
                m_cycle_start = to;
                m_cycle_end = vertex;
                return true;
            }
        }
        m_vertices_state[vertex] = VertexState::Exited;
        return false;
    }

    CycleChecker::CycleChecker(const Graph& graph)
        : CycleChecker(graph.AsConnectionList())
    {
    }

    CycleChecker::CycleChecker
        (const ConnectionList & graph)
            : m_vertices_state(graph.size(), VertexState::NotVisited)
            , m_cycle_start(-1)
            , m_cycle_end(-1)
            , m_parents(graph.size(), -1)
            , m_cycle_found(false)
            , m_cycle(0)
    {
        for (size_t i = 0; i < graph.size(); i++)
        {
            if (m_vertices_state[i] == VertexState::NotVisited &&
                dfs(graph, i))
            {
                m_cycle_found = true;
                for (int v = m_cycle_end; v != m_cycle_start; v = m_parents[v])
                {
                    m_cycle.push_back(v);
                }
                m_cycle.push_back(m_cycle_start);
                std::reverse(m_cycle.begin(), m_cycle.end());
                break;
            }
        }
    }

    CycleChecker::CycleChecker
        (const ConnectionMatrix & graph)
            : CycleChecker(Graph::CM2CL(graph))
    {
    }

    CycleChecker::CycleChecker
        (const ListOfEdges & graph)
            : CycleChecker(Graph::LOE2CL(graph))
    {
    }

    bool CycleChecker::HasCycle() const
    {
        return m_cycle_found;
    }

    std::vector<CycleChecker::VertexType> CycleChecker::GetCycle() const
    {
        return m_cycle;
    }


}

