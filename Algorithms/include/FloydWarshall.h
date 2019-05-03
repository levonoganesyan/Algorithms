#pragma once

#include"Graph.h"

namespace algo
{
    class FloydWarshall
    {
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
        using WeightType = Graph::WeightType;

        ConnectionMatrix m_distances;
        Matrix<int> m_parents;
        void get_path(int from, int to, std::vector<int>& path);
    public:

        FloydWarshall(const ConnectionList& connection_list);
        FloydWarshall(const ConnectionMatrix& connection_matrix);
        FloydWarshall(const ListOfEdges& list_of_edges);
        WeightType GetDistance(int from, int to);
        std::vector<int> GetDistance(int from);
        std::vector<int> GetPath(int from, int to);

    };
}
