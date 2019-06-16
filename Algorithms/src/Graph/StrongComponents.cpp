#include "Graph\StrongComponents.h"
#include "Graph\Toposort.h"


namespace algo
{
    void StrongComponents::dfs(const ConnectionList & graph, int vertex)
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
    StrongComponents::StrongComponents(const ConnectionList & graph)
        : m_used(Graph::GetSize(graph))
    {
        Toposort toposort(graph);
        auto sorted_vertices = toposort.GetNewVerticesIndices();

        ConnectionList reversed_graph = Graph::Reverse(graph);

        size_t graph_size = Graph::GetSize(graph);

        for (int i = 0; i < graph_size; i++)
        {
            if (!m_used[sorted_vertices[i]])
            {
                m_components.push_back({});
                dfs(reversed_graph, sorted_vertices[i]);
            }
        }
        for (auto& component : m_components)
        {
            std::sort(component.begin(), component.end());
        }
        std::sort(m_components.begin(), m_components.end());
    }

    StrongComponents::StrongComponents(const ConnectionMatrix & graph)
        : StrongComponents(Graph::ConnectionMatrixToConnectionList(graph))
    {
    }

    StrongComponents::StrongComponents(const ListOfEdges & graph)
        : StrongComponents(Graph::ListOfEdgesToConnectionList(graph))
    {
    }

    int StrongComponents::GetCount() const
    {
        return m_components.size();
    }

    std::vector<Graph::VertexType> StrongComponents::GetComponent(int index) const
    {
        return m_components[index];
    }

    Matrix<Graph::VertexType> StrongComponents::GetComponents() const
    {
        return m_components;
    }



}

