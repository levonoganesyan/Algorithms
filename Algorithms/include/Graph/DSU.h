#pragma once

#include<Graph/Graph.h>

namespace algo
{
    class DSU
    {
        using Vertex = Graph::VertexType;

        std::vector<Vertex> m_parent;
        std::vector<int> m_size;
    public:
        DSU(int number_of_elements = 0);

        Vertex GetParent(Vertex vertex);
        void Union(Vertex first, Vertex second);
        int MakeNewSet();
        std::vector<Vertex> GetGroup(Vertex element);
    };
}

