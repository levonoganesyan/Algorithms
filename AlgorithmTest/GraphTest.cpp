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
#include"Graph/LCA.h"
#include"Graph/CutPoints.h"
#include"Graph/Bridges.h"
#include"Graph/ChromaticNumber.h"
#include"Graph/FordBellman.h"
#include"Graph/Euler.h"
#include"Graph/PruferCode.h"
#include<algorithm>
#include<numeric>

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
        EXPECT_FALSE(cycle_checker.HasCycle());
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
        EXPECT_TRUE(cycle_checker.HasCycle());
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
TEST(TreeTest, GraphTest)
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
        algo::Graph graph(edges_graph);
        EXPECT_TRUE(graph.isTree());
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
        algo::Graph graph(edges_graph);
        EXPECT_FALSE(graph.isTree());
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1, 1},
            {1, 2, 1},
            {2, 3, 1},
            {3, 4, 1},
            {4, 5, 1},
            {5, 1, 1},
        };
        algo::Graph::UniqifyListOfEdges(edges_graph);
        algo::Graph graph(edges_graph);
        EXPECT_FALSE(graph.isTree());
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1, 1},
            {1, 2, 1},
            {2, 3, 1},
            {3, 4, 1},
            {4, 5, 1},
            {5, 0, 1},
        };
        algo::Graph::UniqifyListOfEdges(edges_graph);
        algo::Graph graph(edges_graph);
        EXPECT_FALSE(graph.isTree());
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1, 1},
            {1, 7, 1},
            {2, 3, 1},
            {3, 4, 1},
            {4, 5, 1},
            {5, 0, 1},
        };
        algo::Graph::UniqifyListOfEdges(edges_graph);
        algo::Graph graph(edges_graph);
        EXPECT_TRUE(graph.isTree());
    }
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

TEST(LCATest, GraphTest)
{
    algo::Graph graph = algo::Graph::ListOfEdges{
        {0, 1},
        {0, 2},
        {0, 3},
        {1, 4},
        {1, 5},
        {4, 9},
        {9, 13},
        {5, 10},
        {5, 11},
        {11, 14},
        {11, 15},
        {2, 6},
        {2, 7},
        {6, 12},
        {12, 16},
        {16, 17},
        {3, 8}
    };

    algo::LCA lca(graph);
    EXPECT_EQ(lca.Get(13, 17), 0);
    EXPECT_EQ(lca.Get(14, 10), 5);
    EXPECT_EQ(lca.Get(2, 17), 2);
    EXPECT_EQ(lca.Get(17, 2), 2);
    EXPECT_EQ(lca.Get(9, 14), 1);
    EXPECT_EQ(lca.Get(8, 8), 8);
}

TEST(CutPointsTest, GraphTest)
{
    {
        algo::Graph graph = algo::Graph::MakeUndirected(
            algo::Graph::ListOfEdges{
            {0, 1},
            {0, 2},
            {0, 3},
            {1, 4},
            {1, 5},
            {4, 9},
            {9, 13},
            {5, 10},
            {5, 11},
            {11, 14},
            {11, 15},
            {2, 6},
            {2, 7},
            {6, 12},
            {12, 16},
            {16, 17},
            {3, 8}
            });

        algo::CutPoints cp(graph);
        std::vector<int> etalon = { 0, 1, 2, 3, 4, 5, 6, 9, 11, 12, 16 };
        EXPECT_EQ(cp.Get(), etalon);
    }
    {
        algo::Graph graph = algo::Graph::MakeUndirected(
            algo::Graph::ListOfEdges{
            {0, 1},
            {1, 5},
            {2, 5},
            {4, 5},
            {2, 7},
            {3, 6},
            {3, 7},
            {6, 7},
            });

        algo::CutPoints cp(graph);
        std::vector<int> etalon = { 1, 2, 5, 7 };
        EXPECT_EQ(cp.Get(), etalon);
    }
}

TEST(FordBellmanTest, GraphTest)
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
        algo::FordBellman ford_bellman(edges_graph, i);
        EXPECT_EQ(ford_bellman.GetDistance(), floyd_warshall.GetDistance(i));
        ford_bellman = algo::FordBellman(algo::Graph(edges_graph), i);
        EXPECT_EQ(ford_bellman.GetDistance(), floyd_warshall.GetDistance(i));
        int number_of_path_tests = 20;
        while (number_of_path_tests--)
        {
            int to = (int)algo::random(0, number_of_vertices);
            EXPECT_EQ(ford_bellman.GetPath(to), floyd_warshall.GetPath(i, to));
        }
    }
}

TEST(EulerTest, GraphTest)
{
    /*algo::Graph::ConnectionList edges_graph = { 
        {1, 6}, 
        {0, 2, 3, 6}, 
        {1, 3},
        {1, 2, 4, 6},
        {3, 5},
        {0, 1, 3, 5},
        {4, 6}
    };*/


    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1},
            {0, 6},
            {1, 2},
            {1, 3},
            // {1, 6},
            // {2, 3},
            {3, 4},
            {3, 6},
            {4, 5},
            {5, 6},
        };
        edges_graph = algo::Graph::MakeUndirected(edges_graph);
        algo::Euler euler(edges_graph);
        EXPECT_FALSE(euler.HasPath());
        EXPECT_FALSE(euler.HasCycle());
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1},
            {0, 6},
            {1, 2},
            {1, 3},
            // {1, 6},
            {2, 3},
            {3, 4},
            {3, 6},
            {4, 5},
            {5, 6},
        };
        edges_graph = algo::Graph::MakeUndirected(edges_graph);
        algo::Euler euler(edges_graph);
        EXPECT_TRUE(euler.HasPath());
        EXPECT_FALSE(euler.HasCycle());
        std::vector<int> etalon = { 6, 5, 4, 3, 2, 1, 3, 6, 0, 1 };
        EXPECT_EQ(euler.GetCycle(), etalon);
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1},
            {0, 2},
            {0, 3},
            {0, 5},
            {1, 2},
            {1, 3},
            {1, 4},
            {2, 3},
            {2, 5},
            {3, 4}
        };
        edges_graph = algo::Graph::MakeUndirected(edges_graph);
        algo::Euler euler(edges_graph);
        EXPECT_TRUE(euler.HasPath());
        EXPECT_TRUE(euler.HasCycle());
        std::vector<int> etalon = { 0, 5, 2, 3, 4, 1, 3, 0, 2, 1, 0 };
        EXPECT_EQ(euler.GetCycle(), etalon);
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 2},
            {0, 4},
            {0, 5},
            {0, 3},
            {1, 3},
            {1, 5},
            {2, 4},
            {3, 4},
            {3, 5},
            {4, 5}
        };
        edges_graph = algo::Graph::MakeUndirected(edges_graph);
        algo::Euler euler(edges_graph);
        EXPECT_TRUE(euler.HasPath());
        EXPECT_TRUE(euler.HasCycle());
        std::vector<int> etalon = { 0, 5, 4, 3, 5, 1, 3, 0, 4, 2, 0 };
        EXPECT_EQ(euler.GetCycle(), etalon);
    }
    {
        algo::Graph::ListOfEdges edges_graph = {
            {0, 1},
            {0, 6},
            {1, 2},
            {1, 3},
            {1, 6},
            {2, 3},
            {3, 4},
            {3, 6},
            {4, 5},
            {5, 6},
        };
        edges_graph = algo::Graph::MakeUndirected(edges_graph);
        algo::Euler euler(edges_graph);
        EXPECT_TRUE(euler.HasPath());
        EXPECT_TRUE(euler.HasCycle());
    }
}

TEST(PruferCodeTest, GraphTest)
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
        algo::Graph::MakeUndirected(edges_graph);
        algo::Graph graph(edges_graph);
        algo::PruferCode prufer;
        std::vector<int> etalon = {1, 1, 3, 2};
        EXPECT_EQ(prufer.Encode(graph), etalon);
    }
}


TEST(BridgesTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges{
                {0, 1},
                {0, 2},
                {0, 3},
                {1, 4},
                {1, 5},
                {4, 9},
                {9, 13},
                {5, 10},
                {5, 11},
                {11, 14},
                {11, 15},
                {2, 6},
                {2, 7},
                {6, 12},
                {12, 16},
                {16, 17},
                {3, 8}
        };
        edges = algo::Graph::MakeUndirected(edges);
        algo::Graph graph = edges;

        algo::Bridges br(graph);
        std::vector<algo::Graph::Edge> etalon = edges;
        EXPECT_EQ(algo::Graph::MakeUndirected(br.Get()),
            algo::Graph::MakeUndirected(etalon));
    }
    {
        algo::Graph graph = algo::Graph::MakeUndirected(
            algo::Graph::ListOfEdges{
            {0, 1},
            {1, 5},
            {2, 5},
            {4, 5},
            {2, 7},
            {3, 6},
            {3, 7},
            {6, 7},
            });

        algo::Bridges br(graph);
        std::vector<algo::Graph::Edge> etalon{
            {0, 1},
            {1, 5},
            {2, 5},
            {4, 5},
            {2, 7},
        };
        EXPECT_EQ(algo::Graph::MakeUndirected(br.Get()),
            algo::Graph::MakeUndirected(etalon));
    }
}

TEST(ChromaticNumberTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges{
                {0, 1},
                {0, 2},
                {0, 3},
                {1, 4},
                {1, 5},
                {4, 9},
                {9, 13},
                {5, 10},
                {5, 11},
                {11, 14},
                {11, 15},
                {2, 6},
                {2, 7},
                {6, 12},
                {12, 16},
                {16, 17},
                {3, 8}
        };
        edges = algo::Graph::MakeUndirected(edges);
        algo::Graph graph = edges;

        algo::ChromaticNumber cn(graph);
        EXPECT_EQ(cn.GetNumber(), 2);
    }
    {
        algo::Graph graph = algo::Graph::MakeUndirected(
            algo::Graph::ListOfEdges{
            {0, 1},
            {1, 5},
            {2, 5},
            {4, 5},
            {2, 7},
            {3, 6},
            {3, 7},
            {6, 7},
            });
        algo::ChromaticNumber cn(graph);
        EXPECT_EQ(cn.GetNumber(), 3);
    }
    {
        algo::Graph graph = algo::Graph::MakeUndirected(
            algo::Graph::ListOfEdges{
            {0, 1},
            {0, 2},
            {0, 3},
            {1, 2},
            {1, 3},
            {2, 3},
            });
        algo::ChromaticNumber cn(graph);
        EXPECT_EQ(cn.GetNumber(), 4);
    }
}


TEST(BipartiteTest, GraphTest)
{
    {
        algo::Graph::ListOfEdges edges{
                {0, 1},
                {0, 2},
                {0, 3},
                {1, 4},
                {1, 5},
                {4, 9},
                {9, 13},
                {5, 10},
                {5, 11},
                {11, 14},
                {11, 15},
                {2, 6},
                {2, 7},
                {6, 12},
                {12, 16},
                {16, 17},
                {3, 8}
        };
        edges = algo::Graph::MakeUndirected(edges);
        algo::Graph graph = edges;
        EXPECT_TRUE(graph.isBipartite());
    }
    {
        algo::Graph graph = algo::Graph::MakeUndirected(
            algo::Graph::ListOfEdges{
            {0, 1},
            {1, 5},
            {2, 5},
            {4, 5},
            {2, 7},
            {3, 6},
            {3, 7},
            {6, 7},
            });
        EXPECT_FALSE(graph.isBipartite());
    }
    {
        algo::Graph graph = algo::Graph::MakeUndirected(
            algo::Graph::ListOfEdges{
            {0, 3},
            {0, 4},
            {1, 3},
            {1, 4},
            {1, 5},
            {2, 4},
            {2, 5},
            });
        EXPECT_TRUE(graph.isBipartite());
    }
    {
        algo::Graph graph = algo::Graph::MakeUndirected(
            algo::Graph::ListOfEdges{
            {0, 3},
            {0, 4},
            {0, 1},
            {1, 3},
            {1, 4},
            {1, 5},
            {2, 4},
            {2, 5},
            });
        EXPECT_FALSE(graph.isBipartite());
    }
}




