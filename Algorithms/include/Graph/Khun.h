#pragma once
#include<vector>
#include"Graph.h"
#include"Utils.h"
namespace algo
{
    class Khun
    {
    public:
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;

    private:
        int n;
        std::vector<Graph::WeightType> m_distance;
        std::vector<int> m_parents;
        int m_start_vertex;

        bool dfs(const ConnectionList& graph, int v);

    public:
        Khun(const Graph& graph);
        Khun(const ConnectionList& graph);
        Khun(const ConnectionMatrix& graph);
        Khun(const ListOfEdges& graph);

        std::vector<Graph::Edge> Get() const;

    };
}


