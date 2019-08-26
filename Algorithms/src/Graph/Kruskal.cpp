#include<Graph/Kruskal.h>

namespace algo
{
    Kruskal::Kruskal(const Graph& graph)
        : Kruskal(graph.AsListOfEdges())
    {
    }
    Kruskal::Kruskal(const ConnectionList & graph)
        : Kruskal(Graph::CL2LOE(graph))
    {
    }
    Kruskal::Kruskal(const ConnectionMatrix & graph)
        : Kruskal(Graph::CM2LOE(graph))
    {
    }
    Kruskal::Kruskal(const ListOfEdges& graph)
        : m_dsu(Graph::GetSize(graph))
        , m_cost(0)
    {
        std::set<Graph::Edge, Graph::WeightLess> 
                all_edges(graph.begin(), graph.end());

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
        std::sort(m_spanning_tree.begin(), m_spanning_tree.end());
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

