#pragma once
#include<Graph\Graph.h>
namespace algo
{

    class Toposort
    {
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
        using VertexType = Graph::VertexType;

        using VertexState = Graph::VertexState;

        std::vector<VertexType> m_sorted_vertices;
        std::vector<char> m_used;

        void dfs(const ConnectionList & graph, int vertex);

    public:
		Toposort(const Graph& graph);
		Toposort(const ConnectionList& graph);
        Toposort(const ConnectionMatrix& graph);
        Toposort(const ListOfEdges& graph);

        std::vector<VertexType> GetNewVerticesIndices() const;
    };

}
