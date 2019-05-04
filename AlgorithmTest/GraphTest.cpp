#include"pch.h"
#include"Graph.h"
#include"Dijkstra.h"
#include"FloydWarshall.h"
#include<algorithm>

TEST(GraphConvertTest, GraphTest)
{
    int number_of_vertices = 4;
    int number_of_edges = 10;
    algo::Graph::WeightType weight = 10;
    auto edges_graph = algo::Graph::RandomGraph
                (number_of_vertices, number_of_edges, weight);
    using Edge = algo::Graph::Edge;
    algo::Graph::UniqifyListOfEdges(edges_graph);

    algo::Graph::ConnectionMatrix matrix_graph =
        algo::Graph::ListOfEdgesToConnectionMatrix(edges_graph);

    algo::Graph::ConnectionList list_graph =
        algo::Graph::ListOfEdgesToConnectionList(edges_graph);


    EXPECT_EQ(edges_graph,
        algo::Graph::ConnectionMatrixToListOfEdges(matrix_graph));

    EXPECT_EQ(edges_graph,
        algo::Graph::ConnectionListToListOfEdges(list_graph));


    EXPECT_EQ(matrix_graph,
        algo::Graph::ListOfEdgesToConnectionMatrix(edges_graph));

    EXPECT_EQ(matrix_graph,
        algo::Graph::ConnectionListToConnectionMatrix(list_graph));


    EXPECT_EQ(list_graph,
        algo::Graph::ListOfEdgesToConnectionList(edges_graph));

    EXPECT_EQ(list_graph,
        algo::Graph::ConnectionMatrixToConnectionList(matrix_graph));
}


TEST(ShortestPathTest, GraphTest)
{
    int number_of_vertices = 100;
    int number_of_edges = 5000;
    algo::Graph::WeightType weight = 10000;
    auto edges_graph = algo::Graph::RandomGraph
                (number_of_vertices, number_of_edges, weight);
    algo::Graph::UniqifyListOfEdges(edges_graph);
    // edges_graph = { {0,1,1}, {0,2,2}, {1,2,2}, {1,3,2} };
    algo::FloydWarshall floyd_warshall(edges_graph);
    for (int i = 0; i < number_of_vertices; ++i)
    {
        algo::Dijkstra dikstra(edges_graph, i);
        EXPECT_EQ(dikstra.GetDistance(), floyd_warshall.GetDistance(i));
        int number_of_path_tests = 20;
        while (number_of_path_tests--)
        {
            int to = (int)algo::random(0, number_of_vertices);
            EXPECT_EQ(dikstra.GetPath(to), floyd_warshall.GetPath(i, to));
        }
    }
}





