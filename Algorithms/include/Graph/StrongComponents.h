#pragma once
#include<Graph/Graph.h>
#include<Graph/DSU.h>
namespace algo
{
    class StrongComponents
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
        StrongComponents(const ConnectionList & graph);
        StrongComponents(const ConnectionMatrix& graph);
        StrongComponents(const ListOfEdges& graph);

        int GetCount() const;
        std::vector<Graph::VertexType> GetComponent(int index) const;
        Matrix<Graph::VertexType> GetComponents() const;
    };
}