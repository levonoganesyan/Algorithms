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
        using WeightType = double;
        using Color = int;
        struct Edge
        {
            VertexType from;
            VertexType to;
            WeightType weight;
            Edge();
            Edge(VertexType from, VertexType to, WeightType weight);
            Edge(VertexType from, VertexType to);
            bool operator< (const Edge& other) const;
            // TODO: investigate why adding const to operator==
            //       cause compile error
            bool operator==(const Edge& other);
            // Edge(int to, int weight = 1);
        };

        enum class VertexState {
            NotVisited,
            Visited,
            Exited,
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

        class WeightLess
        {
        public:
            typedef Edge value_type;
            typedef Edge first_argument_type;
            typedef Edge second_argument_type;
            typedef bool result_type;
            
            bool
                operator()
                    (const Edge& first, const Edge& second) const;
        };
        class WeightGreater
        {
        public:
            typedef Edge value_type;
            typedef Edge first_argument_type;
            typedef Edge second_argument_type;
            typedef bool result_type;

            bool
                operator()
                    (const Edge& first, const Edge& second) const;
        };

        static ConnectionList
            Reverse
            (const ConnectionList& graph);

        static ListOfEdges
            Reverse
            (const ListOfEdges& graph);

        static ConnectionMatrix
            Reverse
            (const ConnectionMatrix& graph);

        static ConnectionList
            ListOfEdgesToConnectionList
                (const ListOfEdges& list_of_edges, bool oriented = true);
        static ConnectionList
            LOE2CL
                (const ListOfEdges& list_of_edges, bool oriented = true);

        static ConnectionList
            ConnectionMatrixToConnectionList
                (const ConnectionMatrix& connection_matrix);
        static ConnectionList
            CM2CL
                (const ConnectionMatrix& connection_matrix);

        static ListOfEdges
            ConnectionListToListOfEdges
                (const ConnectionList& connection_list);
        static ListOfEdges
            CL2LOE
                (const ConnectionList& connection_list);

        static ListOfEdges
            ConnectionMatrixToListOfEdges
                (const ConnectionMatrix& connection_matrix);
        static ListOfEdges
            CM2LOE
                (const ConnectionMatrix& connection_matrix);

        static ConnectionMatrix
            ListOfEdgesToConnectionMatrix
                (const ListOfEdges& list_of_edges, bool oriented = true);
        static ConnectionMatrix
            LOE2CM
            (const ListOfEdges& list_of_edges, bool oriented = true);

        static ConnectionMatrix
            ConnectionListToConnectionMatrix
                (const ConnectionList& connection_list);
        static ConnectionMatrix
            CL2CM
                (const ConnectionList& connection_list);

        static ConnectionMatrix
            MakeUndirected
            (ConnectionMatrix& connection_matrix);

        static ConnectionList
            MakeUndirected
            (ConnectionList& connection_list);

        static ListOfEdges
            MakeUndirected
            (ListOfEdges& list_of_edges);

        static size_t
            GetSize
            (const ConnectionMatrix& connection_matrix);

        static size_t
            GetSize
            (const ConnectionList& connection_list);

        static size_t
            GetSize
            (const ListOfEdges& list_of_edges);

        static ListOfEdges
            RandomGraph(int number_of_vertices = 1000,
                        int number_of_edges = 100000,
                        WeightType weight = 10);

        static void
            UniqifyListOfEdges
                (ListOfEdges& list_of_edges);

        static void
            NormalizeListOfEdges
                (ListOfEdges& list_of_edges);
        
        Graph(const ConnectionList& connection_list);
        Graph(const ConnectionMatrix& connection_matrix);
        Graph(const ListOfEdges& list_of_edges);
        ConnectionList AsConnectionList() const;
        ConnectionMatrix AsConnectionMatrix() const;
        ListOfEdges AsListOfEdges() const;
        size_t GetSize() const;
        bool isBipartite() const;
        bool isTree() const;

    private:
        mutable ConnectionList m_connection_list;
        mutable ConnectionMatrix m_connection_matrix;
        mutable ListOfEdges m_list_of_edges;
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
    bool operator==(const Graph::Edge& first, const Graph::Edge& second);
    inline void PrintTo(const Graph::Edge &edge, ::std::ostream *os)
    {
        *os << "{" << edge.from 
            << ", " << edge.to 
            << ", " << edge.weight
            << "}";
    }
};


