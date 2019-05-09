#include <Graph\DSU.h>

namespace algo
{

    DSU::DSU(int number_of_elements)
        : m_parent(number_of_elements)
        , m_size(number_of_elements)
    {
        for (int i = 0; i < m_parent.size(); ++i)
        {
            m_parent[i] = i;
            m_size[i] = 1;
        }
    }

    DSU::Vertex DSU::GetParent(DSU::Vertex vertex)
    {
        return m_parent[vertex] == vertex
                    ? vertex
                    : m_parent[vertex] = GetParent(m_parent[vertex]);
    }

    void DSU::Union(DSU::Vertex first, DSU::Vertex second)
    {
        first = GetParent(first);
        second = GetParent(second);
        if (first != second)
        {
            if (m_size[first] > m_size[second])
            {
                std::swap(first, second);
            }
            m_parent[first] = second;
            m_size[second] += m_size[first];
        }

    }

    int DSU::MakeNewSet()
    {
        m_parent.push_back(m_parent.size());
        m_size.push_back(1);
        return m_parent.size() - 1;
    }

    std::vector<DSU::Vertex> DSU::GetGroup(DSU::Vertex element)
    {
        std::vector<DSU::Vertex> group;
        element = GetParent(element);
        for (int i = 0; i < m_parent.size(); ++i)
        {
            if (GetParent(i) == element)
            {
                group.push_back(i);
            }
        }
        return group;
    }
}
