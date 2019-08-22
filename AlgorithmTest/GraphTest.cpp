#include"pch.h"
#include"Graph/DSU.h"
#include"Graph/Graph.h"
#include"Graph/Dijkstra.h"
#include"Graph/Toposort.h"
#include"Graph/CycleChecker.h"
#include"Graph/FloydWarshall.h"
#include"Graph/Kruskal.h"
#include"Graph/Components.h"
#include"Graph/StrongComponents.h"
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


    EXPECT_EQ(edges_graph, algo::Graph::CM2LOE(matrix_graph));
    EXPECT_EQ(edges_graph, algo::Graph::CL2LOE(list_graph));
    
	EXPECT_EQ(matrix_graph, algo::Graph::LOE2CM(edges_graph));
    EXPECT_EQ(matrix_graph, algo::Graph::CL2CM(list_graph));
    
	EXPECT_EQ(list_graph, algo::Graph::LOE2CL(edges_graph));
    EXPECT_EQ(list_graph, algo::Graph::CM2CL(matrix_graph));

	algo::Graph graph(edges_graph);
	EXPECT_EQ(edges_graph, graph.AsListOfEdges());
	EXPECT_EQ(matrix_graph, graph.AsConnectionMatrix());
	EXPECT_EQ(list_graph, graph.AsConnectionList());

	graph = algo::Graph(list_graph);
	EXPECT_EQ(edges_graph, graph.AsListOfEdges());
	EXPECT_EQ(matrix_graph, graph.AsConnectionMatrix());
	EXPECT_EQ(list_graph, graph.AsConnectionList());

	graph = algo::Graph(matrix_graph);
	EXPECT_EQ(edges_graph, graph.AsListOfEdges());
	EXPECT_EQ(matrix_graph, graph.AsConnectionMatrix());
	EXPECT_EQ(list_graph, graph.AsConnectionList());


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
		dikstra = algo::Dijkstra(algo::Graph(edges_graph), i);
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
    // TODO: cycle case?
    //{
    //    algo::Graph::ListOfEdges edges_graph = {
    //        {3, 0, 1},
    //        {0, 1, 1},
    //        {1, 4, 1},
    //        {1, 3, 1},
    //        {2, 3, 1},
    //        {2, 5, 1},
    //    };
    //    algo::Graph::UniqifyListOfEdges(edges_graph);
    //    algo::Graph::MakeUndirected(edges_graph);
    //    // algo::Toposort toposort(edges_graph);
    //    EXPECT_THROW((algo::Toposort(edges_graph)), std::logic_error);
    //}
}

TEST(DSUTest, GraphTest)
{
    algo::DSU dsu(6);
    dsu.Union(0, 1);
    EXPECT_EQ(dsu.GetParent(0), dsu.GetParent(1));
    dsu.Union(1, 3);
    EXPECT_EQ(dsu.GetParent(3), dsu.GetParent(0));
    EXPECT_NE(dsu.GetParent(2), dsu.GetParent(3));
    dsu.Union(3, 2);
    EXPECT_EQ(dsu.GetParent(2), dsu.GetParent(3));
    dsu.Union(5, 2);
    EXPECT_EQ(dsu.GetParent(4), 4);
    dsu.Union(4, 1);
    std::vector<algo::Graph::VertexType> etalon = { 0, 1, 2, 3, 4, 5 };
    EXPECT_EQ(dsu.GetGroup(0), etalon);
}

TEST(KruskalTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1, 100},
            {1, 2, 100},
            {1, 5, 10},
            {2, 3, 10},
            {2, 4, 5},
            {2, 5, 100},
            {2, 6, 10},
            {3, 4, 5},
            {4, 6, 15},
            {5, 6, 10},
        };
        //algo::Graph::MakeUndirected(edges_graph);
        algo::Kruskal kruskal(edges_graph);
        EXPECT_EQ(kruskal.GetCost(), 140);
        algo::Graph::ListOfEdges etalon = {
            {0, 1, 100},
            {1, 5, 10},
            {2, 4, 5},
            {2, 6, 10},
            {3, 4, 5},
            {5, 6, 10},
        };
        EXPECT_EQ(algo::Graph::GetSize(kruskal.GetTree()),
            algo::Graph::GetSize(etalon));

        EXPECT_EQ(kruskal.GetTree(), etalon);
    }
}

TEST(ComponentsTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1, 1},
            {2, 3, 1},
        };
        algo::Graph::MakeUndirected(edges_graph);
        algo::Components components(edges_graph);
        EXPECT_EQ(components.GetCount(), 2);

        std::vector<algo::Graph::VertexType> etalon = { 0, 1 };
        EXPECT_EQ(components.GetComponent(0), etalon);
        etalon = { 2, 3 };
        EXPECT_EQ(components.GetComponent(1), etalon);
    }
    {
        algo::Graph::ConnectionList connection_list = {
            {{0, 1, 1}},
            {{1, 0, 1}},
            {{2, 3, 1}},
            {{3, 2, 1}},
            {},
        };
        algo::Graph::MakeUndirected(connection_list);
        algo::Components components(connection_list);
        EXPECT_EQ(components.GetCount(), 3);

        std::vector<algo::Graph::VertexType> etalon = { 0, 1 };
        EXPECT_EQ(components.GetComponent(0), etalon);
        etalon = { 2, 3 };
        EXPECT_EQ(components.GetComponent(1), etalon);
        etalon = { 4 };
        EXPECT_EQ(components.GetComponent(2), etalon);
    }
}

TEST(StrongComponentsTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1},
            {1, 2},
            {2, 0},
            {0, 3},
            {0, 4},
            {3, 4},
            {3, 5},
            {4, 5},
            {5, 3},
            {2, 7},
            {6, 7},
            {7, 6},
        };
        // algo::Graph::MakeUndirected(edges_graph);
        algo::StrongComponents components(edges_graph);
        ASSERT_EQ(components.GetCount(), 3);

        std::vector<algo::Graph::VertexType> etalon = { 0, 1, 2 };
        EXPECT_EQ(components.GetComponent(0), etalon);
        etalon = { 3, 4, 5 };
        EXPECT_EQ(components.GetComponent(1), etalon);
        etalon = { 6, 7 };
        EXPECT_EQ(components.GetComponent(2), etalon);
    }

    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1},
            {1, 2},
            {2, 0},
            {0, 3},
            {0, 4},
            {3, 4},
            {3, 5},
            {4, 5},
            {5, 3},
            {2, 7},
            {6, 7},
            {7, 6},
        };
        int graph_size = (int)algo::Graph::GetSize(edges_graph);
        for (auto& edge : edges_graph)
        {
            edge.to = graph_size - edge.to - 1;
            edge.from = graph_size - edge.from - 1;
        }
        std::sort(edges_graph.begin(), edges_graph.end());
        // algo::Graph::MakeUndirected(edges_graph);
        algo::StrongComponents components(edges_graph);
        ASSERT_EQ(components.GetCount(), 3);

        std::vector<algo::Graph::VertexType> etalon = { 0, 1 };
        EXPECT_EQ(components.GetComponent(0), etalon);
        etalon = { 2, 3, 4 };
        EXPECT_EQ(components.GetComponent(1), etalon);
        etalon = { 5, 6, 7 };
        EXPECT_EQ(components.GetComponent(2), etalon);
    }
}





