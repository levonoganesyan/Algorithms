#pragma once
#include<vector>
#include<Graph/Graph.h>


namespace algo
{
    class Components
    {
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
        using VertexType = Graph::VertexType;

        Matrix<VertexType> m_components;
        std::vector<VertexType> m_used;
    private:
        void dfs(const ConnectionList & graph, int vertex);
    public:
        Components(const ConnectionList & graph);
        Components(const ConnectionMatrix& graph);
        Components(const ListOfEdges& graph);

        size_t GetCount() const;
        std::vector<Graph::VertexType> GetComponent(int index) const;
        Matrix<Graph::VertexType> GetComponents() const;
    };
}