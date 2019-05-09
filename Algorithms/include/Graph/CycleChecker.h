#pragma once
#include<vector>
#include<Graph/Graph.h>
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
        CycleChecker(const ConnectionList & graph);

        CycleChecker(const ConnectionMatrix& graph);

        CycleChecker(const ListOfEdges& graph);

        bool HasCycle() const;
        std::vector<VertexType> GetCycle() const;


    };
}
