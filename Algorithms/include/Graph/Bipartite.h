#pragma once
#include<vector>
#include"Graph.h"
#include"Utils.h"
namespace algo
{
    class Bipartite
    {
    public:
        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;

    private:
        std::vector<char> m_used;
        bool dfs(int v);
    public:
        Bipartite(const ConnectionList & graph);

        Bipartite(const ConnectionMatrix& graph);

        Bipartite(const ListOfEdges& graph);

    };
}


