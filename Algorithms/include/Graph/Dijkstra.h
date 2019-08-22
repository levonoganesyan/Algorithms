#pragma once
#include<vector>
#include"Graph.h"
#include"Utils.h"
namespace algo
{
    class Dijkstra
    {
    public:
        // using Edge = std::pair<int, int>;
        // template<typename WeightType = int>
        // using WeightedEdge = std::pair<std::pair<int, int>, int>;
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;

    private:
        // std::vector<std::vector<int>> m_graph;
        std::vector<Graph::WeightType> m_distance;
        std::vector<int> m_parents;
        int m_start_vertex;


    public:
		Dijkstra(const Graph& graph,
			int start_vertex);

		Dijkstra(const ConnectionList& graph,
			int start_vertex);

        Dijkstra(const ConnectionMatrix& graph,
                int start_vertex);

        Dijkstra(const ListOfEdges& graph,
                int start_vertex);

        int GetDistance(int to) const;
        std::vector<int> GetDistance() const;
        std::vector<int> GetPath(int to) const;

    };
}


