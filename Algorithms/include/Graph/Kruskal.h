#pragma once
#include<Graph/Graph.h>
#include<Graph/DSU.h>
namespace algo
{
    class Kruskal
    {
    private:
        algo::DSU m_dsu;
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
    public:
        Kruskal(const ConnectionList & graph);
        Kruskal(const ConnectionMatrix& graph);
        Kruskal(ListOfEdges graph);

    };
}
