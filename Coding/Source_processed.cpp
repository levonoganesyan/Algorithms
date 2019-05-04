#include <iostream>
#pragma once

#include<vector>
#include<memory>
#pragma once
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<cassert>
#include<queue>
#include<set>
#include<map>

namespace algo
{
    const int Inf = INT_MAX;
    const long long LInf = LLONG_MAX;

    template<typename T, typename... Others>
    T max(T first, Others... others);

    template<typename T>
    T max(T first);

    template<typename T, typename... Others>
    T min(T first, Others... others);

    template<typename T>
    T min(T first);

    template<typename Container>
    void input_container(std::istream& in,
                         int& n,
                         Container& container);

    template<typename Container>
    void output_container(std::ostream& out,
                          const Container& container,
                          const std::string& delimiter = " ");

    template<typename Container, typename T>
    void sum_container(const Container& container, T& sum);


    template <typename T>
    using Matrix = std::vector<std::vector<T>>;

    template <typename T>
    Matrix<T> createMatrix(size_t n, size_t m, T etalon = T());

    double random(double min, double max);
}

#pragma once
#include<algorithm>
#include<random>
namespace algo
{
    template<typename T, typename... Others>
    inline T max(T first, Others... others)
    {
        return std::max(first, max<T>(others...));
    }
    template<typename T>
    inline T max(T first)
    {
        return first;
    }

    template<typename T, typename... Others>
    inline T min(T first, Others... others)
    {
        return std::min(first, min(others...));
    }
    template<typename T>
    inline T min(T first)
    {
        return first;
    }

    template<typename Container, typename T>
    inline void sum_container(const Container& container, T& sum)
    {
        for (auto& elem : container)
        {
            sum += elem;
        }
    }

    template<typename T>
    inline Matrix<T> createMatrix(size_t n, size_t m, T etalon)
    {
        return Matrix<T>(n, std::vector<T>(m, etalon));
    }

    inline double random(double min, double max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(min, max);
        return dist(mt);
    }
    
    template<typename Container>
    inline void input_container(std::istream& in,
                         int& n,
                         Container& container)
    {
        in >> n;
        container.resize(n);
        for (auto& elem : container)
        {
            in >> elem;
        }
    }
    
    template<typename Container>
    inline void output_container(std::ostream& out,
                          const Container& container,
                          const std::string& delimiter)
    {
        for (auto& elem : container)
        {
            out << elem << delimiter;
        }
    }
}





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
            // bool operator==(const Edge& other);
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
                (ListOfEdges list_of_edges, bool oriented = true);

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
                (const ListOfEdges& list_of_edges, bool oriented = true);

        static ConnectionMatrix
            ConnectionListToConnectionMatrix
                (const ConnectionList& connection_list);

        static ListOfEdges
            RandomGraph(int number_of_vertices = 1000,
                        int number_of_edges = 100000,
                        WeightType weight = 10);

        static void
            UniqifyListOfEdges
                (ListOfEdges& list_of_edges);

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
    bool operator==(const Graph::Edge& first, const Graph::Edge& second);
    inline void PrintTo(const Graph::Edge &edge, ::std::ostream *os)
    {
        *os << "{" << edge.from 
            << ", " << edge.to 
            << ", " << edge.weight
            << "}";
    }
};


#pragma once


namespace algo
{

#define in_vec(in, n, c, t) \
        int n; \
        std::vector<t> c; \
        algo::input_container(in, n, c)

#define cin_vec(n, c, t) \
        in_vec(std::cin, n, c, t)

#define in_vec_int(in, n, c) \
        in_vec(in, n, c, int)

#define cin_vec_int(n, c) \
        cin_vec(n, c, int)

#define out_vec_delim(out, c, d) \
        algo::output_container(out, c, d)

#define out_vec(out, c) \
        algo::output_container(out, c)

#define cout_vec_delim(c, d) \
        algo::output_container(std::cout, c, d)

#define cout_vec(c, d) \
        algo::output_container(std::cout, c)

#define sum_vec(c, s, t) \
        t s = 0; \
        algo::sum_container(c, s)

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

}

algo::Graph::ConnectionList
    algo::Graph::ListOfEdgesToConnectionList
        (algo::Graph::ListOfEdges list_of_edges, bool oriented)
{
    ConnectionList connection_list;
    for (const auto& edge : list_of_edges)
    {
        int from = edge.from;
        int to = edge.to;
        connection_list.resize(algo::max<int>(from + 1, to + 1,
                                    (int)connection_list.size()));
        connection_list[from].emplace_back(from, to, edge.weight);
        if (!oriented)
        {
            connection_list[to].emplace_back(to, from, edge.weight);
        }
    }
    return connection_list;
}

algo::Graph::ConnectionList 
    algo::Graph::ConnectionMatrixToConnectionList
        (const ConnectionMatrix & connection_matrix)
{
    ConnectionList connection_list(connection_matrix.size());
    for (size_t i = 0; i < connection_matrix.size(); ++i)
    {
        for (size_t j = 0; j < connection_matrix[i].size(); ++j)
        {
            if (connection_matrix[i][j])
            {
                Graph::WeightType weight = connection_matrix[i][j];
                connection_list[i].emplace_back(i, j, weight);
            }
        }
    }
    return connection_list;
}

algo::Graph::ListOfEdges 
    algo::Graph::ConnectionListToListOfEdges
        (const ConnectionList & connection_list)
{
    ListOfEdges list_of_edges;
    for (size_t i = 0; i < connection_list.size(); ++i)
    {
        for (size_t j = 0; j < connection_list[i].size(); ++j)
        {
            int from = connection_list[i][j].from;
            int to = connection_list[i][j].to;
            Graph::WeightType weight = connection_list[i][j].weight;
            list_of_edges.emplace_back(from, to, weight);
        }
    }
    return list_of_edges;
}

algo::Graph::ListOfEdges 
    algo::Graph::ConnectionMatrixToListOfEdges
        (const ConnectionMatrix & connection_matrix)
{
    ListOfEdges list_of_edges;
    for (size_t i = 0; i < connection_matrix.size(); ++i)
    {
        for (size_t j = i; j < connection_matrix[i].size(); ++j)
        {
            if (connection_matrix[i][j])
            {
                Graph::WeightType weight = connection_matrix[i][j];
                list_of_edges.emplace_back(i, j, weight);
            }
        }
    }
    return list_of_edges;
}

algo::Graph::ConnectionMatrix
    algo::Graph::ListOfEdgesToConnectionMatrix
        (const ListOfEdges & list_of_edges, bool oriented)
{
    size_t max_size = 0;
    for (const auto& edge : list_of_edges)
    {
        max_size = algo::max<size_t>(edge.from + 1,
                                     edge.to + 1,
                                     max_size);
    }
    ConnectionMatrix connection_matrix = 
                    algo::createMatrix<Graph::WeightType>
                            (max_size, max_size);

    for (const auto& edge : list_of_edges)
    {
        int from = edge.from;
        int to = edge.to;
        WeightType w = edge.weight;
        connection_matrix[from][to] = w;
        if(!oriented)
            connection_matrix[to][from] = w;
    }
    return connection_matrix;
}

algo::Graph::ConnectionMatrix 
    algo::Graph::ConnectionListToConnectionMatrix
        (const ConnectionList & connection_list)
{
    ConnectionMatrix connection_matrix =
       algo::createMatrix<Graph::WeightType>
          (connection_list.size(), connection_list.size());
    for (size_t i = 0; i < connection_list.size(); ++i)
    {
        for (size_t j = 0; j < connection_list[i].size(); ++j)
        {
            int to = connection_list[i][j].to;
            Graph::WeightType weight = connection_list[i][j].weight;
            connection_matrix[i][to] = weight;
        }
    }
    return connection_matrix;
}
#pragma warning(push)
#pragma warning(disable: 4244) // possible loss of data
algo::Graph::ListOfEdges 
    algo::Graph::RandomGraph
        (int number_of_vertices, int number_of_edges, WeightType weight)
{
    ListOfEdges list_of_edges;
    for (int i = 0; i < number_of_edges; i++)
    {
        Graph::VertexType from = algo::random(0, number_of_vertices);
        Graph::VertexType to = algo::random(0, number_of_vertices);
        while (from == to)
        {
            to = algo::random(0, number_of_vertices);
        }
        if (from > to)
        {
            std::swap(from, to);
        }
        // change 2-100
        Graph::WeightType w = algo::random(1, weight);
        list_of_edges.emplace_back(from, to, w);
    }
    return list_of_edges;
}
void
    algo::Graph::UniqifyListOfEdges
        (ListOfEdges& list_of_edges)
{
    std::sort(list_of_edges.begin(), list_of_edges.end(),
        [](const Edge& first, const Edge& second)
    {
        if (first.from != second.from)
            return first.from < second.from;
        if (first.to != second.to)
            return first.to < second.to;
        return first.weight < second.weight;
    }
    );
    list_of_edges.erase(
        std::unique(list_of_edges.begin(), list_of_edges.end(),
            [](const Edge& first, const Edge& second)
            {
                return first.from == second.from &&
                    first.to == second.to;
            }
    ), list_of_edges.end());


}
#pragma warning(pop)

algo::Graph::Edge::Edge(int from, int to, int weight)
    : from(from)
    , to(to)
    , weight(weight)
{}

//algo::Graph::Edge::Edge(int to, int weight)
//    : Edge(-1, to, weight)
//{
//}

algo::Graph::Edge::Edge()
    : Edge(-1,-1,-1)
{
}

bool 
    algo::operator==
        (const Graph::Edge & first, const Graph::Edge & second)
{
    return first.from == second.from &&
        first.to == second.to &&
        first.weight == second.weight;
}

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}




