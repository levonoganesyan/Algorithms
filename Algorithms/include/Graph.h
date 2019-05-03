#pragma once

#include<vector>
#include<memory>
#include"Utils.h"
namespace algo
{
    class Graph
    {
    public:
        using VertexType = int;
        using WeightType = int;
        struct Edge
        {
            VertexType from;
            VertexType to;
            WeightType weight;
            Edge();
            Edge(int from, int to, int weight);
            // Edge(int to, int weight = 1);
        };


        using ConnectionList = Matrix<Edge>;
        using ConnectionMatrix = Matrix<WeightType>;
        using ListOfEdges = std::vector<Edge>;

        /*enum class Type
        {
            ConnectionList,
            ConnectionMatrix,
            ListOfEdges,
        };*/


        static ConnectionList
            ListOfEdgesToConnectionList
                (const ListOfEdges& list_of_edges, bool oriented = true);

        static ConnectionList
            ConnectionMatrixToConnectionList
                (const ConnectionMatrix& connection_matrix);

        static ListOfEdges
            ConnectionListToListOfEdges
                (const ConnectionList& connection_list);

        static ListOfEdges
            ConnectionMatrixToListOfEdges
                (const ConnectionMatrix& connection_matrix);

        static ConnectionMatrix
            ListOfEdgesToConnectionMatrix
                (const ListOfEdges& list_of_edges, bool oriented = false);

        static ConnectionMatrix
            ConnectionListToConnectionMatrix
                (const ConnectionList& connection_list);

    private:
        /* template<typename EdgeType = int>
         class Node
         {
             std::set<
                    std::pair<
                             std::shared_ptr<Node>,
                             EdgeType
                             >
                    > m_neighbours;

             int m_index;
         public:
             Node(int index);
             void AddEdge(std::shared_ptr<Node> neighbour,
                          EdgeType weight = EdgeType());

             void Clean();

             bool operator< (std::shared_ptr<Node> other)
             {
                 return this->m_index < other->m_index;
             }
         };
         */
        /*
        std::vector<std::vector<int>> m_graph;
    public:
        Graph(const std::vector<std::vector<int>>& graph, )*/
    };

    //class GraphTypeTag {};
    //class ConnectionListTag : public GraphTypeTag {};
    //class ConnectionMatrixTag : public GraphTypeTag {};
    //class ListOfEdgesTag : public GraphTypeTag {};

};


