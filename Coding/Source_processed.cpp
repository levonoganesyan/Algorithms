#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <sstream>
#pragma once
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
    Matrix<T> CreateMatrix(size_t n, T etalon = T());

    template <typename T>
    Matrix<T> CreateMatrix(size_t n, size_t m, T etalon = T());

    template <typename T>
    void CreateMatrix(Matrix<T>& matrix, size_t n, T etalon = T());

    template <typename T>
    void CreateMatrix(Matrix<T>& matrix, size_t n, size_t m, T etalon = T());

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
    inline Matrix<T> CreateMatrix(size_t n, T etalon)
    {
        return Matrix<T>(n, std::vector<T>(n, etalon));
    }

    template<typename T>
    inline Matrix<T> CreateMatrix(size_t n, size_t m, T etalon)
    {
        return Matrix<T>(n, std::vector<T>(m, etalon));
    }

    template<typename T>
    inline void CreateMatrix(Matrix<T>& matrix, size_t n, T etalon)
    {
        matrix = Matrix<T>(n, std::vector<T>(n, etalon));
    }

    template<typename T>
    inline void CreateMatrix(Matrix<T>& matrix, size_t n, size_t m, T etalon)
    {
        matrix = Matrix<T>(n, std::vector<T>(m, etalon));
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
#define so(v) std::sort(all(v))
#define rall(v) v.rbegin(), v.rend()

}

#pragma once
#include<vector>
namespace algo
{
    class CycleChecker
    {
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
        using VertexType = Graph::VertexType;

        using VertexState = Graph::VertexState;

        std::vector<VertexState> m_vertices_state;

        std::vector<VertexType> m_parents;
        int m_cycle_start, m_cycle_end;
        
        
        bool m_cycle_found;
        std::vector<VertexType> m_cycle;

    private:
        bool dfs(const ConnectionList & graph, int vertex);
    public:
        CycleChecker(const Graph& graph);
        CycleChecker(const ConnectionList& graph);
        CycleChecker(const ConnectionMatrix& graph);
        CycleChecker(const ListOfEdges& graph);

        bool HasCycle() const;
        std::vector<VertexType> GetCycle() const;


    };
}
#include<algorithm>
namespace algo
{
    bool
        CycleChecker::dfs
            (const ConnectionList & graph, int vertex)
    {
        m_vertices_state[vertex] = VertexState::Visited;
        for (size_t i = 0; i < graph[vertex].size(); ++i)
        {
            int to = graph[vertex][i].to;
            if (m_vertices_state[to] == VertexState::NotVisited)
            {
                m_parents[to] = vertex;
                if (dfs(graph, to))
                {
                    return true;
                }
            }
            else if (m_vertices_state[to] == VertexState::Visited)
            {
                m_cycle_start = to;
                m_cycle_end = vertex;
                return true;
            }
        }
        m_vertices_state[vertex] = VertexState::Exited;
        return false;
    }

    CycleChecker::CycleChecker(const Graph& graph)
        : CycleChecker(graph.AsConnectionList())
    {
    }

    CycleChecker::CycleChecker
        (const ConnectionList & graph)
            : m_vertices_state(graph.size(), VertexState::NotVisited)
            , m_cycle_start(-1)
            , m_cycle_end(-1)
            , m_parents(graph.size(), -1)
            , m_cycle_found(false)
            , m_cycle(0)
    {
        for (size_t i = 0; i < graph.size(); i++)
        {
            if (m_vertices_state[i] == VertexState::NotVisited &&
                dfs(graph, i))
            {
                m_cycle_found = true;
                for (int v = m_cycle_end; v != m_cycle_start; v = m_parents[v])
                {
                    m_cycle.push_back(v);
                }
                m_cycle.push_back(m_cycle_start);
                std::reverse(m_cycle.begin(), m_cycle.end());
                break;
            }
        }
    }

    CycleChecker::CycleChecker
        (const ConnectionMatrix & graph)
            : CycleChecker(Graph::CM2CL(graph))
    {
    }

    CycleChecker::CycleChecker
        (const ListOfEdges & graph)
            : CycleChecker(Graph::LOE2CL(graph))
    {
    }

    bool CycleChecker::HasCycle() const
    {
        return m_cycle_found;
    }

    std::vector<CycleChecker::VertexType> CycleChecker::GetCycle() const
    {
        return m_cycle;
    }


}

#pragma once
namespace algo
{
    class ChromaticNumber
    {
    private:

        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
        using Edge = Graph::Edge;
        using Color = Graph::Color;

        std::vector<Color> m_colors;
        int m_chromatic_number;

        void dfs(const ConnectionList& graph, int v);

    public:
        ChromaticNumber(const Graph& graph);
        ChromaticNumber(const ConnectionList& graph);
        ChromaticNumber(const ConnectionMatrix& graph);
        ChromaticNumber(const ListOfEdges& graph);
        std::vector<Color> GetColors() const;
        int GetNumber() const;
    };
}
namespace algo
{
    void ChromaticNumber::dfs(const ConnectionList& graph, int v)
    {
        if (m_colors[v] != -1)
        {
            return;
        }
        std::vector<Color> used_colors;
        for (int i = 0; i < graph[v].size(); ++i)
        {
            int to = graph[v][i].to;
            if (m_colors[to] != -1)
            {
                used_colors.push_back(m_colors[to]);
            }
        }
        so(used_colors);
        int color = -1;
        for (int i = 0; i < used_colors.size(); ++i)
        {
            if (used_colors[i] != i)
            {
                color = i;
                break;
            }
        }
        if (color == -1)
        {
            color = used_colors.size();
        }
        m_colors[v] = color;
        for (int i = 0; i < graph[v].size(); ++i)
        {
            int to = graph[v][i].to;
            dfs(graph, to);
        }
    }

    ChromaticNumber::ChromaticNumber(const Graph& graph)
        : ChromaticNumber(graph.AsConnectionList())
    {
    }

    ChromaticNumber::ChromaticNumber(const ConnectionList& graph)
        : m_colors(graph.size(), -1)
        , m_chromatic_number(0)
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            if (m_colors[i] == -1)
            {
                dfs(graph, i);
            }
        }
        m_chromatic_number = *std::max_element(m_colors.begin(), 
                                               m_colors.end()) + 1;
    }

    ChromaticNumber::ChromaticNumber(const ConnectionMatrix& graph)
        : ChromaticNumber(Graph::CM2CL(graph))
    {
    }

    ChromaticNumber::ChromaticNumber(const ListOfEdges& graph)
        : ChromaticNumber(Graph::LOE2CL(graph))
    {
    }
    std::vector<ChromaticNumber::Color> ChromaticNumber::GetColors() const
    {
        return m_colors;
    }
    int ChromaticNumber::GetNumber() const
    {
        return m_chromatic_number;
    }
}
namespace algo
{

    bool 
        Graph::WeightLess::operator()
        (const Edge& first, const Edge& second) const
    {
        if (first.weight != second.weight)
            return first.weight < second.weight;
        return first < second;
    }
    bool
        Graph::WeightGreater::operator()
        (const Edge& first, const Edge& second) const
    {
        if (first.weight != second.weight)
            return first.weight > second.weight;
        return second < first;
    }
    


    Graph::ConnectionList Graph::Reverse(const ConnectionList& graph)
    {
        ConnectionList new_graph(GetSize(graph));
        for (auto& vertices : graph)
            for (auto& neighbour : vertices)
                new_graph[neighbour.to].emplace_back(neighbour.to, neighbour.from, neighbour.weight);
        return new_graph;
    }

    Graph::ListOfEdges Graph::Reverse(const ListOfEdges& graph)
    {
        ListOfEdges new_graph; 
        for (size_t i = 0; i < graph.size(); ++i)
        {
            new_graph.emplace_back(graph[i].to, graph[i].from, graph[i].weight);
        }
        return new_graph;
    }

    Graph::ConnectionMatrix Graph::Reverse(const ConnectionMatrix& graph)
    {
        ConnectionMatrix new_graph;
        CreateMatrix(new_graph, GetSize(graph));
        for (size_t i = 0; i < graph.size(); ++i)
            for (size_t j = 0; j < graph[i].size(); ++j)
                new_graph[j][i] = graph[i][j];
        return new_graph;
    }

    Graph::ConnectionList
        Graph::ListOfEdgesToConnectionList
            (const Graph::ListOfEdges& list_of_edges, bool oriented)
    {
        ConnectionList connection_list;
        for (const auto& edge : list_of_edges)
        {
            int from = edge.from;
            int to = edge.to;
            connection_list.resize(max<int>(from + 1, to + 1,
                                    (int)connection_list.size()));
            connection_list[from].emplace_back(from, to, edge.weight);
            if (!oriented)
            {
                connection_list[to].emplace_back(to, from, edge.weight);
            }
        }
        return connection_list;
    }

    Graph::ConnectionList 
        Graph::LOE2CL
            (const ListOfEdges& list_of_edges, bool oriented)
    {
        return ListOfEdgesToConnectionList(list_of_edges, oriented);
    }

    Graph::ConnectionList
        Graph::ConnectionMatrixToConnectionList
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

    Graph::ConnectionList 
        Graph::CM2CL
        (const ConnectionMatrix& connection_matrix)
    {
        return ConnectionMatrixToConnectionList(connection_matrix);
    }

    Graph::ListOfEdges
        Graph::ConnectionListToListOfEdges
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

    Graph::ListOfEdges Graph::CL2LOE(const ConnectionList& connection_list)
    {
        return ConnectionListToListOfEdges(connection_list);
    }

    Graph::ListOfEdges
        Graph::ConnectionMatrixToListOfEdges
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

    Graph::ListOfEdges 
        Graph::CM2LOE
        (const ConnectionMatrix& connection_matrix)
    {
        return ConnectionMatrixToListOfEdges(connection_matrix);
    }

    Graph::ConnectionMatrix
        Graph::ListOfEdgesToConnectionMatrix
        (const ListOfEdges & list_of_edges, bool oriented)
    {
        size_t max_size = 0;
        for (const auto& edge : list_of_edges)
        {
            max_size = max<size_t>(edge.from + 1,
                edge.to + 1,
                max_size);
        }
        ConnectionMatrix connection_matrix =
            CreateMatrix<Graph::WeightType>
            (max_size, max_size);

        for (const auto& edge : list_of_edges)
        {
            int from = edge.from;
            int to = edge.to;
            WeightType w = edge.weight;
            connection_matrix[from][to] = w;
            if (!oriented)
                connection_matrix[to][from] = w;
        }
        return connection_matrix;
    }

    Graph::ConnectionMatrix 
        Graph::LOE2CM
        (const ListOfEdges& list_of_edges, bool oriented)
    {
        return ListOfEdgesToConnectionMatrix(list_of_edges, oriented);
    }

    Graph::ConnectionMatrix
        Graph::ConnectionListToConnectionMatrix
        (const ConnectionList & connection_list)
    {
        ConnectionMatrix connection_matrix =
            CreateMatrix<Graph::WeightType>
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
    Graph::ConnectionMatrix Graph::CL2CM(const ConnectionList& connection_list)
    {
        return ConnectionListToConnectionMatrix(connection_list);
    }

    Graph::ConnectionMatrix
        Graph::MakeUndirected
            (ConnectionMatrix & connection_matrix)
    {
        for (size_t i = 0; i < connection_matrix.size(); ++i)
        {
            for (size_t j = 0; j < connection_matrix[i].size(); ++j)
            {
                if (connection_matrix[i][j])
                {
                    connection_matrix[j][i] = connection_matrix[i][j];
                }
            }
        }
        return connection_matrix;
    }
    Graph::ConnectionList
        Graph::MakeUndirected
            (ConnectionList & connection_list)
    {
        ConnectionList new_connection_list = connection_list;
        
        for (size_t i = 0; i < connection_list.size(); ++i)
        {
            for (size_t j = 0; j < connection_list[i].size(); ++j)
            {
                Edge edge;
                edge.from = connection_list[i][j].to;
                edge.to = connection_list[i][j].from;
                edge.weight = connection_list[i][j].weight;
                new_connection_list[edge.from].push_back(edge);
            }
        }
        for (size_t i = 0; i < new_connection_list.size(); ++i)
        {
            std::sort(new_connection_list[i].begin(), 
                      new_connection_list[i].end());

            auto it = std::unique(new_connection_list[i].begin(),
                                  new_connection_list[i].end());

            new_connection_list[i].erase(it, new_connection_list[i].end());
        }
        connection_list = new_connection_list;
        return connection_list;
        
    }
    Graph::ListOfEdges
        Graph::MakeUndirected
            (ListOfEdges & list_of_edges)
    {
        ListOfEdges new_list_of_edges = list_of_edges;
        for (size_t i = 0; i < list_of_edges.size(); ++i)
        {
            Edge edge = list_of_edges[i];
            std::swap(edge.to, edge.from);
            new_list_of_edges.push_back(edge);
        }
        Graph::UniqifyListOfEdges(new_list_of_edges);
        list_of_edges = new_list_of_edges;
        return list_of_edges;
    }
    size_t Graph::GetSize(const ConnectionMatrix & connection_matrix)
    {
        return connection_matrix.size();
    }
    size_t Graph::GetSize(const ConnectionList & connection_list)
    {
        return connection_list.size();
    }
    size_t Graph::GetSize(const ListOfEdges & list_of_edges)
    {
        size_t list_size = 0;
        for (size_t i = 0; i < list_of_edges.size(); ++i)
        {
            list_size = algo::max<size_t>(list_size,
                                          list_of_edges[i].to + 1,
                                          list_of_edges[i].from + 1);
        }
        return list_size;
    }
#pragma warning(push)
#pragma warning(disable: 4244) // possible loss of data
    Graph::ListOfEdges
        Graph::RandomGraph
            (int number_of_vertices, int number_of_edges, WeightType weight)
    {
        ListOfEdges list_of_edges;
        for (int i = 0; i < number_of_edges; i++)
        {
            Graph::VertexType from = random(0, number_of_vertices);
            Graph::VertexType to = random(0, number_of_vertices);
            while (from == to)
            {
                to = random(0, number_of_vertices);
            }
            if (from > to)
            {
                std::swap(from, to);
            }
            // change 2-100
            Graph::WeightType w = random(1, weight);
            list_of_edges.emplace_back(from, to, w);
        }
        return list_of_edges;
    }
    void
        Graph::UniqifyListOfEdges
            (ListOfEdges& list_of_edges)
    {
        std::sort(list_of_edges.begin(), list_of_edges.end());
        list_of_edges.erase(
            std::unique(list_of_edges.begin(), list_of_edges.end()
        ), list_of_edges.end());


    }
    Graph::Graph(const ConnectionList& connection_list)
        : m_connection_list(connection_list)
    {
    }
    Graph::Graph(const ConnectionMatrix& connection_matrix)
        : m_connection_matrix(connection_matrix)
    {
    }
    Graph::Graph(const ListOfEdges& list_of_edges)
        : m_list_of_edges(list_of_edges)
    {
    }
    Graph::ConnectionList Graph::AsConnectionList() const
    {
        if (m_connection_list.empty())
        {
            if (!m_connection_matrix.empty())
            {
                m_connection_list = Graph::CM2CL(m_connection_matrix);
            }
            else
            {
                m_connection_list = Graph::LOE2CL(m_list_of_edges);
            }
        }
        return m_connection_list;
    }
    Graph::ConnectionMatrix Graph::AsConnectionMatrix() const
    {
        if (m_connection_matrix.empty())
        {
            if (!m_connection_list.empty())
            {
                m_connection_matrix = Graph::CL2CM(m_connection_list);
            }
            else
            {
                m_connection_matrix = Graph::LOE2CM(m_list_of_edges);
            }
        }
        return m_connection_matrix;
    }
    Graph::ListOfEdges Graph::AsListOfEdges() const
    {
        if (m_list_of_edges.empty())
        {
            if (!m_connection_list.empty())
            {
                m_list_of_edges = Graph::CL2LOE(m_connection_list);
            }
            else
            {
                m_list_of_edges = Graph::CM2LOE(m_connection_matrix);
            }
        }
        return m_list_of_edges;
    }
    size_t Graph::GetSize() const
    {
        return Graph::GetSize(this->AsConnectionList());
    }
    bool Graph::isBipartite() const
    {
        return ChromaticNumber(*this).GetNumber() <= 2;
    }
    bool Graph::isTree() const
    {
        CycleChecker cc(*this);
        return !cc.HasCycle();
    }
#pragma warning(pop)

    Graph::Edge::Edge(VertexType from, VertexType to, WeightType weight)
        : from(from)
        , to(to)
        , weight(weight)
    {}

    Graph::Edge::Edge(VertexType from, VertexType to)
        : Edge(from, to, 1)
    {}

    bool Graph::Edge::operator<(const Edge & other) const
    {
        if (this->from != other.from)
            return this->from < other.from;
        if (this->to != other.to)
            return this->to < other.to;
        return this->weight < other.weight;
    }

    bool Graph::Edge::operator==(const Edge & other)
    {
        return this->from == other.from &&
            this->to == other.to;
    }

    //Graph::Edge::Edge(int to, int weight)
    //    : Edge(-1, to, weight)
    //{
    //}

    Graph::Edge::Edge()
        : Edge(-1, -1, -1)
    {
    }

    bool
        operator==
        (const Graph::Edge & first, const Graph::Edge & second)
    {
        return first.from == second.from &&
            first.to == second.to &&
            first.weight == second.weight;
    }


}

namespace algo
{

    class Toposort
    {
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
        using VertexType = Graph::VertexType;

        using VertexState = Graph::VertexState;

        std::vector<VertexType> m_sorted_vertices;
        std::vector<char> m_used;

        void dfs(const ConnectionList & graph, int vertex);

    public:
        Toposort(const Graph& graph);
        Toposort(const ConnectionList& graph);
        Toposort(const ConnectionMatrix& graph);
        Toposort(const ListOfEdges& graph);

        std::vector<VertexType> GetNewVerticesIndices() const;
    };

}
#include<exception>
#include<algorithm>
namespace algo
{
    void Toposort::dfs(const ConnectionList & graph, int vertex)
    {
        m_used[vertex] = true;
        for (size_t i = 0; i < graph[vertex].size(); ++i)
        {
            int to = graph[vertex][i].to;
            if (!m_used[to])
            {
                dfs(graph, to);
            }
        }
        m_sorted_vertices.push_back(vertex);
    }

    Toposort::Toposort(const Graph& graph)
        : Toposort(graph.AsConnectionList())
    {
    }

    Toposort::Toposort(const ConnectionList & graph)
        : m_sorted_vertices(0)
        , m_used(graph.size())
    {
        /*CycleChecker cycle_checker(graph);
        if (cycle_checker.HasCycle())
        {
            throw std::logic_error("Graph must be acyclic for toposort");
        }*/
        for (size_t i = 0; i < m_used.size(); ++i)
        {
            if (!m_used[i])
            {
                dfs(graph, i);
            }
        }
        std::reverse(m_sorted_vertices.begin(), m_sorted_vertices.end());
    }

    Toposort::Toposort(const ConnectionMatrix & graph)
        : Toposort(Graph::CM2CL(graph))
    {
    }
    Toposort::Toposort(const ListOfEdges & graph)
        : Toposort(Graph::LOE2CL(graph))
    {
    }
    std::vector<Graph::VertexType> Toposort::GetNewVerticesIndices() const
    {
        return m_sorted_vertices;
    }
}



#pragma once
#include<iterator>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<functional>
namespace algo
{
    //template<typename Iter>
    //void sort(const Iter& first, const Iter& second);

    template<typename Iter>
    void BubbleSort(Iter first, Iter last)
    {
        for (Iter i = first; i != last; i = std::next(i))
        {
            for (Iter j = first; j < i; j = std::next(j))
            {
                if (*i < *j)
                {
                    std::iter_swap(i, j);
                }
            }
        }
    }
    template<typename Iter>
    void SelectionSort(Iter first, Iter last)
    {
        for (Iter i = first; i != last; i = std::next(i))
        {
            Iter min = i;
            for (Iter j = i; j < last; j = std::next(j))
            {
                if (*j < *min)
                {
                    min = j;
                }
            }
            std::iter_swap(i, min);
        }
    }

    template<typename Iter>
    void InsertionSort(Iter first, Iter last)
    {
        for (Iter i = std::next(first); i != last; i = std::next(i))
        {
            Iter temp = i;
            while (temp != first)
            {
                if (*temp < *std::prev(temp))
                {
                    std::iter_swap(temp, std::prev(temp));
                }
                temp = std::prev(temp);
            }
        }
    }

    template<typename Iter>
    void RadixSort(Iter first, Iter last)
        // this sort must work only for ints
    {
        std::vector<int> vec(first, last); 
        int power_of_ten = 1;
        std::vector<std::vector<int>> buckets(10);
        for (int pow = 0; pow < 10; ++pow)
        {
            for (Iter i = vec.begin(); i != vec.end(); i = std::next(i))
            {
                buckets[(*i) / power_of_ten % 10].push_back(*i);
            }
            vec.clear();
            for (int i = 0; i < buckets.size(); ++i)
            {
                vec.insert(vec.end(), buckets[i].begin(), buckets[i].end());
                buckets[i].clear();
            }
            power_of_ten *= 10;
        }
        std::copy(vec.begin(), vec.end(), first);
    }
    template<typename Iter>
    void HeapSort(Iter first, Iter last)
    {
        using type = typename Iter::value_type;
        std::priority_queue<type,
            std::vector<type>,
            std::greater<type>> pq(first, last);
        while (!pq.empty())
        {
            *first = pq.top();
            first = std::next(first);
            pq.pop();
        }
    }

    template<typename Iter>
    void merge(Iter first_begin, Iter first_end,
                Iter second_begin, Iter second_end, 
                Iter out_begin)
    {
        while (first_begin < first_end && second_begin < second_end)
        {
            *out_begin++ = *first_begin < *second_begin ? *first_begin++ : *second_begin++;
        }
        while (first_begin < first_end)
        {
            *out_begin++ = *first_begin++;
        }
        while (second_begin < second_end)
        {
            *out_begin++ = *second_begin++;
        }
    }

    template<typename Iter>
    void MergeSort(Iter first, Iter last)
    {
        int size = std::distance(first, last);
        if (size == 1)
            return;
        int half = size / 2;
        using type = typename Iter::value_type;
        Iter mid = first;
        std::advance(mid, half);
        std::vector<type> f_v(first, mid);
        std::vector<type> s_v(mid, last);
        MergeSort(f_v.begin(), f_v.end());
        MergeSort(s_v.begin(), s_v.end());
        merge(f_v.begin(), f_v.end(), s_v.begin(), s_v.end(), first);
    }

    template<typename Iter>
    Iter partition(Iter first, Iter last)
    {
        typename Iter::value_type pivot = *first;
        Iter out = first;

        for (Iter temp = std::next(first); temp != last; temp = std::next(temp))
        {
            if (*temp < pivot)
            {
                out = std::next(out);
                std::iter_swap(out, temp);
            }
        }
        std::iter_swap(out, first);
        return out;
    }
    
    template<typename Iter>
    void QuickSort(Iter first, Iter last)
    {
        if (std::distance(first, last) > 1)
        {
            Iter mid = partition(first, last);
            QuickSort(first, mid);
            QuickSort(std::next(mid), last);
        }
    }
}
#pragma once
#include<vector>
#include<functional>
namespace algo
{
    template<typename T>
    class SegmentTree
    {
    public:
        static T min(T a, T b)
        {
            return a < b ? a : b;
        }
        static T max(T a, T b)
        {
            return a > b ? a : b;
        }
        enum class UpdateType
        {
            Assign,
            Sum,
            Product
        };
    private:
        std::vector<T> m_vec;
        std::vector<T> m_tree;
        std::vector<T> m_lazy_prop;
        std::function<T(T, T)> m_tree_logic;
        int m_neutral_element;
        UpdateType m_upd_type;

        void build_tree(int v, int l, int r);
        void update(int pos, T elem, int v, int l, int r);
        // void update(int pos_l, int pos_r, T elem, int v, int l, int r);
        T query(int from, int to, int v, int l, int r) const;
        static int left(int v);
        static int right(int v);
        static int mid(int l, int r);
        void update_one(int& a, int b);
    public:
        SegmentTree(const std::vector<T>& vec,
                    const std::function<T(T, T)>& tree_logic,
                    int neutral_element,
                    UpdateType upd_type = UpdateType::Assign);
        
        void build_tree();
        void update(int pos, T elem);
        // void update(int pos_l, int pos_r, T elem);
        T query(int from, int to) const;
        int size() const;
    };
}


namespace algo
{
    template<typename T>
    inline void SegmentTree<T>::build_tree(int v, int l, int r)
    {
        if (l == r)
        {
            m_tree[v] = m_vec[l];
        }
        else
        {
            int m = mid(l, r);
            build_tree(left(v), l, m);
            build_tree(right(v), m + 1, r);
            m_tree[v] = m_tree_logic(m_tree[left(v)], m_tree[right(v)]);
        }
    }

    template<typename T>
    inline void SegmentTree<T>::update(int pos, T elem, int v, int l, int r)
    {
        if (l == r)
        {
            update_one(m_tree[v], elem);
            update_one(m_vec[pos], elem);
        }
        else
        {
            int m = mid(l, r);
            if (pos <= m)
            {
                update(pos, elem, left(v), l, m);
            }
            else
            {
                update(pos, elem, right(v), m + 1, r);
            }
            m_tree[v] = m_tree_logic(m_tree[left(v)], m_tree[right(v)]);
        }
    }

    /*template<typename T>
    inline void SegmentTree<T>::update(int pos_l, int pos_r, T elem, int v, int l, int r)
    {
        if (pos_l == l && pos_r == r)
        {
            m_lazy_prop = elem;
        }
    }*/

    template<typename T>
    inline T SegmentTree<T>::query(int from, int to, int v, int l, int r) const
    {
        if (from > to)
        {
            return m_neutral_element;
        }
        if (from == l && to == r)
        {
            return m_tree[v];
        }
        else
        {
            int m = mid(l, r);
            int left_ans = query(from, std::min(m, to), left(v), l, m);
            int right_ans = query(std::max(from, m + 1), to, right(v), m + 1, r);
            return m_tree_logic(left_ans, right_ans);
        }
    }

    template<typename T>
    inline int SegmentTree<T>::left(int v)
    {
        return v << 1;
    }

    template<typename T>
    inline int SegmentTree<T>::right(int v)
    {
        return (v << 1) + 1;
    }

    template<typename T>
    inline int SegmentTree<T>::mid(int l, int r)
    {
        return (l + r) >> 1;
    }

    template<typename T>
    inline void SegmentTree<T>::update_one(int& a, int b)
    {
        switch (m_upd_type)
        {
        case UpdateType::Assign:
            a = b;
            break;
        case UpdateType::Sum:
            a += b;
            break;
        case UpdateType::Product:
            a *= b;
            break;
        default:
            break;
        }
    }

    template<typename T>
    SegmentTree<T>::SegmentTree(const std::vector<T>& vec,
                                const std::function<T(T, T)>& tree_logic,
                                int neutral_element,
                                UpdateType upd_type)
        : m_vec(vec)
        , m_tree_logic(tree_logic)
        , m_neutral_element(neutral_element)
        , m_upd_type(upd_type)
    {
        m_tree.resize(m_vec.size() << 2);
    }

    template<typename T>
    inline void SegmentTree<T>::build_tree()
    {
        build_tree(1, 0, m_vec.size() - 1);
    }

    template<typename T>
    inline void SegmentTree<T>::update(int pos, T elem)
    {
        update(pos, elem, 1, 0, m_vec.size() - 1);
    }

    /*template<typename T>
    inline void SegmentTree<T>::update(int pos_l, int pos_r, T elem)
    {
        if (m_lazy_prop.empty())
        {
            m_lazy_prop.resize(m_tree.size());
        }
        update(pos_l, pos_r, elem, 1, 0, m_vec.size() - 1);
    }*/

    template<typename T>
    inline T SegmentTree<T>::query(int from, int to) const
    {
        return query(from, to, 1, 0, m_vec.size() - 1);
    }
    template<typename T>
    inline int SegmentTree<T>::size() const
    {
        return m_vec.size();
    }
}






using namespace std;

// Test FordBellman
// Test Euler path and cycle

int main()
{
    int n;
    cin >> n;
    algo::SegmentTree<int> tree(std::vector<int>(40000, 0), 
                                std::plus<int>(), 
                                0,
                                algo::SegmentTree<int>::UpdateType::Sum);
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        ans[tree.query(0, x)]++;
        tree.update(x, 1);
    }
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << endl;
    }
}



