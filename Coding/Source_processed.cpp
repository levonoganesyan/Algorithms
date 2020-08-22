#pragma comment(linker, "/STACK:500000000")
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<unordered_set>
#include<set>
#include<iomanip>
#include<queue>
#include<cmath>
#pragma once
#include<vector>
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
#include<limits.h>

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
                new_graph[neighbour.to].emplace_back(neighbour.to, 
                                                    neighbour.from, 
                                                    neighbour.weight);
        return new_graph;
    }

    Graph::ListOfEdges Graph::Reverse(const ListOfEdges& graph)
    {
        ListOfEdges new_graph; 
        for (size_t i = 0; i < graph.size(); ++i)
        {
            new_graph.emplace_back(graph[i].to, 
                                    graph[i].from, 
                                    graph[i].weight);
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
    void Graph::NormalizeListOfEdges(ListOfEdges& list_of_edges)
    {
        for (auto& edge : list_of_edges)
        {
            if (edge.from > edge.to)
            {
                std::swap(edge.from, edge.to);
            }
        }
        UniqifyListOfEdges(list_of_edges);
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
        Dijkstra(const Graph& graph, int start_vertex);
        Dijkstra(const ConnectionList& graph, int start_vertex);
        Dijkstra(const ConnectionMatrix& graph, int start_vertex);
        Dijkstra(const ListOfEdges& graph, int start_vertex);

        Graph::WeightType GetDistance(int to) const;
        std::vector<Graph::WeightType> GetDistance() const;
        std::vector<int> GetPath(int to) const;

    };
}


namespace algo
{
    Dijkstra::Dijkstra(const Graph& graph, int start_vertex)
        : Dijkstra(graph.AsConnectionList(), start_vertex)
    {
    }
    Dijkstra::Dijkstra
        (const Dijkstra::ConnectionList & graph,
         int start_vertex)
            : m_start_vertex(start_vertex)
    {
        assert(start_vertex < (int)graph.size());

        m_distance.resize(graph.size(), Inf);
        m_distance[start_vertex] = 0;
        m_parents.resize(graph.size());
        for (size_t i = 0; i < m_parents.size(); ++i)
        {
            m_parents[i] = (int)i;
        }
        std::set<std::pair<Graph::WeightType, int>> queue;
        queue.emplace(0, start_vertex);
        while (!queue.empty())
        {
            int from = queue.begin()->second;
            queue.erase(queue.begin());

            for (size_t i = 0; i < graph[from].size(); ++i)
            {
                int to = graph[from][i].to;
                Graph::WeightType weight = graph[from][i].weight;

                if (m_distance[from] + weight < m_distance[to])
                {
                    queue.erase({ m_distance[to], to });
                    m_distance[to] = m_distance[from] + weight;
                    m_parents[to] = from;
                    queue.insert({ m_distance[to], to });
                }
            }
        }
    }

    Dijkstra::Dijkstra
        (const Dijkstra::ConnectionMatrix& graph,
         int start_vertex)
        : m_start_vertex(start_vertex)
    {
        m_distance.resize(graph.size(), Inf);
        m_distance[start_vertex] = 0;
        m_parents.resize(graph.size());
        for (size_t i = 0; i < m_parents.size(); ++i)
        {
            m_parents[i] = (int)i;
        }
        std::vector<char> used(graph.size());
        for (size_t i = 0; i < graph.size(); ++i)
        {
            size_t v = 0;
            bool first_choose = true;
            for (size_t j = 0; j < graph[i].size(); ++j)
            {
                if (!used[j] && (first_choose ||
                    m_distance[j] < m_distance[v]))
                {
                    v = j;
                    first_choose = false;
                }
            }
            if (m_distance[v] == Inf)
                break;

            used[v] = true;

            for (size_t j = 0; j < graph[i].size(); ++i)
            {
                size_t to = j;
                Graph::WeightType weight = graph[i][j];
                if (m_distance[to] > m_distance[v] + weight)
                {
                    m_distance[to] = m_distance[v] + weight;
                    m_parents[to] = (int)v;
                }
            }
        }
    }

    Dijkstra::Dijkstra
        (const Dijkstra::ListOfEdges& graph,
         int start_vertex) : Dijkstra(Graph::LOE2CL(graph), start_vertex)
    {
    }

    Graph::WeightType
        Dijkstra::GetDistance
            (int to) const
    {
        assert(to < (int)m_distance.size());
        return m_distance[to];
    }

    std::vector<Graph::WeightType>
        Dijkstra::GetDistance
            () const
    {
        return m_distance;
    }


    std::vector<int>
        Dijkstra::GetPath
            (int to) const
    {
        assert(to < (int)m_parents.size());
        std::vector<int> path;
        if (to == m_parents[to])
        {
            return path;
        }
        for (int v = to; v != m_start_vertex; v = m_parents[v])
        {
            path.push_back(v);
        }
        path.push_back(m_start_vertex);
        std::reverse(all(path));
        return path;
    }

}


using namespace std;

map<pair<int, int>, int> cti;
int curr = 0;

algo::Graph::ConnectionList graph;

void matrix_to_graph(const vector<vector<char>>& matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (matrix[i][j] == '#')
                continue;
            if (cti.find({ i, j }) == cti.end())
            {
                cti[{i, j}] = curr++;
            }
            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    if (!l && !k)
                        continue;
                    int x = i + k;
                    int y = j + l;
                    
                    if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size())
                    {
                        if (cti.find({ x, y }) == cti.end())
                        {
                            cti[{x, y}] = curr++;
                        }
                        if (matrix[x][y] != '#')
                        {
                            algo::Graph::Edge e;
                            e.from = cti[{i, j}];
                            e.to   = cti[{x, y}];
                            e.weight = (k == 0 || l == 0) ? 1 : sqrt(2.0);
                            graph[cti[{i, j}]].push_back(e);
                            swap(e.to, e.from);
                            graph[cti[{x, y}]].push_back(e);
                        }
                    }
                }
            }
        }
    }
}

int main() 
{
    const int Inf = 1000000000;
    int n, m;
    cin >> n >> m;
    graph.resize(n * m);
    int k;
    cin >> k;
    double v;
    cin >> v;
    swap(n, m);
    vector<vector<char>> matrix(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> matrix[i][j];

    matrix_to_graph(matrix);

    int x, y;
    cin >> x >> y;
    --x;
    --y;
    swap(x, y);
    double dist = 0;
    for (int i = 0; i < k; ++i)
    {
        algo::Dijkstra dijkstra(graph, cti[{x, y}]);
        int a, b;
        cin >> a >> b;
        --a, --b;
        swap(a, b);
        if (dijkstra.GetDistance(cti[{a, b}]) != algo::Inf)
        {
            dist += dijkstra.GetDistance(cti[{a, b}]);
            x = a;
            y = b;
        }
    }

    cout << fixed << setprecision(2) << dist / v;

}
