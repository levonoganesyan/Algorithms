#include"pch.h"
#include"Graph/Graph.h"
#include"Graph/Dijkstra.h"
#include"Graph/Toposort.h"
#include"Graph/CycleChecker.h"
#include"Graph/FloydWarshall.h"
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


TEST(DijkstraFloydWarshallTest, GraphTest)
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

TEST(MakeUndirectedTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1, 1},
            {1, 4, 1},
            {1, 3, 1},
            {2, 3, 1},
            {2, 5, 1},
        };

        algo::Graph::ListOfEdges etalon = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 3, 1},
            {1, 4, 1},
            {2, 3, 1},
            {2, 5, 1},
            {3, 1, 1},
            {3, 2, 1},
            {4, 1, 1},
            {5, 2, 1},
        };
        algo::Graph::MakeUndirected(edges_graph);
        EXPECT_EQ(edges_graph, etalon);
    }
    {
        algo::Graph::ConnectionMatrix edges_graph = {
            {0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 1, 1},
            {0, 1, 0, 1, 0},
        };

        algo::Graph::ConnectionMatrix etalon = {
            {0, 1, 1, 1, 0},
            {1, 0, 1, 0, 1},
            {1, 1, 0, 1, 0},
            {1, 0, 1, 1, 1},
            {0, 1, 0, 1, 0},
        };
        algo::Graph::MakeUndirected(edges_graph);
        EXPECT_EQ(edges_graph, etalon);
    }
    {

        algo::Graph::ConnectionList edges_graph = {
            {{ 0, 1, 1 }},
            {{ 1, 4, 1 }, { 1, 4, 1 }, { 1, 3, 1 }},
            {{ 2, 3, 1 }, { 2, 5, 1 }},
            {{ 3, 2, 1 }},
            {},
            {}
        };

        algo::Graph::ConnectionList etalon = {
            {{ 0, 1, 1 }},
            {{ 1, 0, 1 }, { 1, 3, 1 }, { 1, 4, 1 }},
            {{ 2, 3, 1 }, { 2, 5, 1 }},
            {{ 3, 1, 1 }, { 3, 2, 1 }},
            {{ 4, 1, 1 }},
            {{ 5, 2, 1 }}
        };

        algo::Graph::MakeUndirected(edges_graph);
        EXPECT_EQ(edges_graph, etalon);
    }
}

TEST(CycleFindingTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1, 1},
            {1, 4, 1},
            {1, 3, 1},
            {2, 3, 1},
            {2, 5, 1},
        };
        algo::Graph::UniqifyListOfEdges(edges_graph);
        algo::CycleChecker cycle_checker(edges_graph);
        EXPECT_EQ(cycle_checker.HasCycle(), false);
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {3, 0, 1},
            {0, 1, 1},
            {1, 4, 1},
            {1, 3, 1},
            {2, 3, 1},
            {2, 5, 1},
        };
        algo::Graph::UniqifyListOfEdges(edges_graph);
        algo::CycleChecker cycle_checker(edges_graph);
        EXPECT_EQ(cycle_checker.HasCycle(), true);
        std::vector<algo::Graph::VertexType> etalon = { 0, 1, 3 };
        EXPECT_EQ(cycle_checker.GetCycle(), etalon);
    }
}


TEST(ToposortTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1, 1},
            {1, 4, 1},
            {1, 3, 1},
            {3, 2, 1},
            {2, 5, 1},
        };
        algo::Graph::UniqifyListOfEdges(edges_graph);
        // algo::Graph::MakeUndirected(edges_graph);
        std::vector<algo::Graph::VertexType> etalon = { 0, 1, 4, 3, 2, 5 };
        algo::Toposort toposort(edges_graph);
        EXPECT_EQ(toposort.GetNewVerticesIndices(), etalon);
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {3, 0, 1},
            {0, 1, 1},
            {1, 4, 1},
            {1, 3, 1},
            {2, 3, 1},
            {2, 5, 1},
        };
        algo::Graph::UniqifyListOfEdges(edges_graph);
        algo::Graph::MakeUndirected(edges_graph);
        // std::vector<algo::Graph::VertexType> etalon = { 0, 1, 4, 3, 2, 5 };
        // algo::Toposort toposort(edges_graph);
        EXPECT_THROW((algo::Toposort(edges_graph)), std::logic_error);
    }
}




