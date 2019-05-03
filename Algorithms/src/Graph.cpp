#include "Graph.h"
#include "Utils.h"
#include "Defines.h"
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
    for (int i = 0; i < connection_matrix.size(); ++i)
    {
        for (int j = 0; j < connection_matrix[i].size(); ++j)
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
    for (int i = 0; i < connection_list.size(); ++i)
    {
        for (int j = 0; j < connection_list[i].size(); ++j)
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
    for (int i = 0; i < connection_matrix.size(); ++i)
    {
        for (int j = i; j < connection_matrix[i].size(); ++j)
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
    for (int i = 0; i < connection_list.size(); ++i)
    {
        for (int j = 0; j < connection_list[i].size(); ++j)
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
