#include "Graph/FloydWarshall.h"

namespace algo
{
    FloydWarshall::FloydWarshall
        (const Graph& graph)
        : FloydWarshall(graph.AsConnectionMatrix())
    {
    }
    FloydWarshall::FloydWarshall
        (const ConnectionList & connection_list)
            : FloydWarshall(Graph::CL2CM(connection_list))
    {
    }

    FloydWarshall::FloydWarshall
        (const ConnectionMatrix & connection_matrix)
    {
        m_distances = connection_matrix;
        size_t matrix_size = connection_matrix.size();
        m_parents = CreateMatrix(matrix_size, matrix_size, -1);
        for (size_t i = 0; i < matrix_size; ++i)
        {
            for (size_t j = 0; j < matrix_size; ++j)
            {
                if (connection_matrix[i][j])
                {
                    m_parents[i][j] = (int)j;
                }
                else
                {
                    if (i != j)
                    {
                        m_distances[i][j] = Inf;
                    }
                }
            }
            m_parents[i][i] = (int)i;
        }
        for (size_t k = 0; k < matrix_size; ++k)
        {
            for (size_t i = 0; i < matrix_size; ++i)
            {
                for (size_t j = 0; j < matrix_size; ++j)
                {
                    if (m_distances[i][k] == Inf ||
                        m_distances[k][j] == Inf)
                    {
                        continue;
                    }
                    WeightType weight =
                        m_distances[i][k] + m_distances[k][j];
                    if (m_distances[i][j] > weight)
                    {
                        m_distances[i][j] = weight;
                        m_parents[i][j] = m_parents[i][k];
                    }
                }
            }
        }
    }

    FloydWarshall::FloydWarshall
        (const ListOfEdges & list_of_edges)
            : FloydWarshall(Graph::LOE2CM(list_of_edges))
    {
    }

    FloydWarshall::WeightType
        FloydWarshall::GetDistance
            (int from, int to) const

    {
        return m_distances[from][to];
    }

    std::vector<Graph::WeightType>
        FloydWarshall::GetDistance
            (int from) const
    {
        return m_distances[from];
    }

    std::vector<int>
        FloydWarshall::GetPath
            (int from, int to) const
    {
        /* std::vector<int> path;
         if (from == to)
             return path;
         get_path(from, to, path);
         return path;*/
        std::vector<int> path;
        if (m_parents[from][to] == -1)
            return path;
        if (from == to)
            return path;
        path.push_back(from);
        while (to != from)
        {
            from = m_parents[from][to];
            path.push_back(from);
        }
        return path;
    }
    void
        FloydWarshall::get_path
            (int from, int to, std::vector<int>& path)
    {
        if (from == to)
        {
            path.push_back(from);
        }
        else if (m_parents[from][to] == -1)
        {
            path.clear();
            return;
        }
        else
        {
            get_path(from, m_parents[from][to], path);
            path.push_back(to);
        }
        /*std::vector<int> path;
        if(m_parents[from][to] == -1)
            return path;
        path.push_back(to);
        while (to != from)
        {
            to = m_parents[from][to];
            path.push_back(to);
        }
        return path;*/
    }

}

