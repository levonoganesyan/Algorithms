#pragma once
#include<vector>
#include"Graph.h"
#include"Utils.h"
namespace algo
{
    class Dijkstra
    {
        // using Edge = std::pair<int, int>;
        // template<typename WeightType = int>
        // using WeightedEdge = std::pair<std::pair<int, int>, int>;

        using ConnectionList = Matrix<Graph::Edge>;
        using ConnectionMatrix = Matrix<char>;
        using ListOfEdges = std::vector<Graph::Edge>;

        // std::vector<std::vector<int>> m_graph;
        std::vector<Graph::WeightType> m_distance;
        std::vector<int> m_parents;
        int m_start_vertex;


        ConnectionList 
            ListOfEdgesToConnectionList
                (const ListOfEdges& list_of_edges);

    public:
        Dijkstra(const ConnectionList & graph, 
                 int start_vertex,
                 ConnectionListTag);

        Dijkstra(const ConnectionMatrix& graph,
                int start_vertex,
                ConnectionMatrixTag);

        Dijkstra(const ListOfEdges& graph,
                int start_vertex,
                ListOfEdgesTag);

        int GetDistance(int to);
        std::vector<int> GetPath(int to);

    };
}


