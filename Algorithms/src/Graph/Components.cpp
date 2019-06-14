#include "Graph\Components.h"


namespace algo
{

    void Components::dfs(const ConnectionList & graph, int vertex)
    {
        m_used[vertex] = true;
        m_components.back().push_back(vertex);
        for (auto& neighbours : graph[vertex])
        {
            if (!m_used[neighbours.to])
            {
                dfs(graph, neighbours.to);
            }
        }
    }

    Components::Components(const ConnectionList & graph)
        : m_used(Graph::GetSize(graph))
    {
        size_t graph_size = Graph::GetSize(graph);
        for (int i = 0; i < graph_size; i++)
        {
            if (!m_used[i])
            {
                m_components.push_back({});
                dfs(graph, i);
            }
        }
    }

    Components::Components(const ConnectionMatrix & graph)
        : Components(Graph::ConnectionMatrixToConnectionList(graph))
    {
    }

    Components::Components(const ListOfEdges & graph)
        : Components(Graph::ListOfEdgesToConnectionList(graph))
    {
    }

    int Components::GetCount() const
    {
        return m_components.size();
    }

    std::vector<Graph::VertexType> Components::GetComponent(int index) const
    {
        return m_components[index];
    }

    Matrix<Graph::VertexType> Components::GetComponents() const
    {
        return m_components;
    }



}
