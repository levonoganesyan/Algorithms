#pragma once
#include<Graph/Graph.h>
#include<Graph/DSU.h>
namespace algo
{
    class Kruskal
    {
    private:
        algo::DSU m_dsu;
        Graph::WeightType m_cost;
        std::vector<Graph::Edge> m_spanning_tree;
        
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;


    public:
        Kruskal(const ConnectionList & graph);
        Kruskal(const ConnectionMatrix& graph);
        Kruskal(const ListOfEdges& graph);

        std::vector<Graph::Edge> GetTree() const;
        Graph::WeightType GetCost() const;

    };
}
