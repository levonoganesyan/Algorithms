#include "Graph/Graph.h"
#include "Utils.h"
#include "Defines.h"
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
    


    Graph::ConnectionList
        Graph::ListOfEdgesToConnectionList
        (Graph::ListOfEdges list_of_edges, bool oriented)
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
            createMatrix<Graph::WeightType>
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
        Graph::ConnectionListToConnectionMatrix
        (const ConnectionList & connection_list)
    {
        ConnectionMatrix connection_matrix =
            createMatrix<Graph::WeightType>
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
    void 
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
    }
    void
        Graph::MakeUndirected
            (ConnectionList & connection_list)
    {
        std::vector<std::vector<Edge>> new_connection_list = connection_list;
        
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
        
    }
    void
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

