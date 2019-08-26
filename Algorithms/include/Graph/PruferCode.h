#pragma once

#include<vector>
#include<string>
#include<Graph/Graph.h>
namespace algo
{
    class PruferCode
    {
    public:
        PruferCode();
        std::vector<int> Encode(const Graph& graph);
        Graph Decode(const std::vector<int>& graph);
    };

}