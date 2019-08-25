#pragma once
#include<vector>
#include<Graph/Graph.h>
namespace algo
{
    class Euler
    {
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
        using VertexType = Graph::VertexType;

        using VertexState = Graph::VertexState;

        bool m_has_path;
        bool m_has_cycle;
        std::vector<VertexType> m_cycle;
        std::set<std::pair<int, int>> m_used;

    private:
        void dfs(const ConnectionList & graph, int vertex);
    public:
        Euler(const Graph& graph);
        Euler(const ConnectionList& graph);
        Euler(const ConnectionMatrix& graph);
        Euler(const ListOfEdges& graph);

        bool HasPath() const;
        bool HasCycle() const;
        std::vector<VertexType> GetCycle() const;


    };
}
