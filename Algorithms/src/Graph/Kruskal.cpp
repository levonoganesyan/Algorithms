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
    Kruskal::Kruskal(ListOfEdges graph)
        : m_dsu(Graph::GetSize(graph))
    {
        std::set<Graph::Edge> all_edges;
    }
}

