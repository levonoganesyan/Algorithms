#pragma once
#include<Graph/Graph.h>

namespace algo
{
    class CutPoints
    {
    private:

        using ConnectionList = Graph::ConnectionList;
        using ConnectionMatrix = Graph::ConnectionMatrix;
        using ListOfEdges = Graph::ListOfEdges;
        using VertexType = Graph::VertexType;

        std::vector<int> m_time_in;
        std::vector<int> m_f_up;
        std::vector<int> m_used;
    
        int m_timer;

        std::vector<VertexType> m_cut_points;

        void dfs(const ConnectionList& graph, int v = 0, int p = -1);

    public:
        CutPoints(const Graph& graph);
        CutPoints(const ConnectionList& graph);
        CutPoints(const ConnectionMatrix& graph);
        CutPoints(const ListOfEdges& graph);
        std::vector<VertexType> Get() const;
    };
}
