#include<Graph/Kruskal.h>

namespace algo
{
    Kruskal::Kruskal(const ConnectionList & graph)
        : Kruskal(Graph::ConnectionListToListOfEdges(graph))
    {
    }
    Kruskal::Kruskal(const ConnectionMatrix & graph)
        : Kruskal(Graph::ConnectionMatrixToConnectionList(graph))
    {
    }
    Kruskal::Kruskal(const ListOfEdges& graph)
        : m_dsu(Graph::GetSize(graph))
    {
        std::set<Graph::WeightType, Graph::Edge> all_edges;

        size_t number_of_edges = graph.size();
        for (size_t i = 0; i < number_of_edges; ++i)
        {
            Graph::Edge e = *all_edges.begin();
            all_edges.erase(all_edges.begin());
            Graph::VertexType from = e.from;
            Graph::VertexType to = e.to;
            Graph::WeightType weight = e.weight;

            if (m_dsu.GetParent(from) != m_dsu.GetParent(to))
            {
                m_cost += weight;
                m_spanning_tree.push_back(e);
                m_dsu.Union(from, to);
            }
        }
    }
    std::vector<Graph::Edge> Kruskal::GetTree() const
    {
        return m_spanning_tree;
    }
    Graph::WeightType Kruskal::GetCost() const
    {
        return m_cost;
    }
}

