#pragma once
#include<Graph/Graph.h>
#include<Graph/DSU.h>
namespace algo
{
    class Kruskal
    {
    private:

        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;


        algo::DSU m_dsu;
        Graph::WeightType m_cost;
        ListOfEdges m_spanning_tree;


    public:
        Kruskal(const ConnectionList & graph);
        Kruskal(const ConnectionMatrix& graph);
        Kruskal(const ListOfEdges& graph);

        std::vector<Graph::Edge> GetTree() const;
        Graph::WeightType GetCost() const;

    };
}
