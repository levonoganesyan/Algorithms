#pragma once
#include<vector>
#include"Graph.h"
#include"Utils.h"
namespace algo
{
    class FordBellman
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


    public:
        FordBellman(const Graph& graph, int start_vertex);
        FordBellman(const ConnectionList& graph, int start_vertex);
        FordBellman(const ConnectionMatrix& graph, int start_vertex);
        FordBellman(const ListOfEdges& graph, int start_vertex);

        int GetDistance(int to) const;
        std::vector<int> GetDistance() const;
        std::vector<int> GetPath(int to) const;

    };
}


