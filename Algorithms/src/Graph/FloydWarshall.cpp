#include "FloydWarshall.h"

algo::FloydWarshall::FloydWarshall
    (const ConnectionList & connection_list)
        : FloydWarshall(
            algo::Graph::ConnectionListToConnectionMatrix
                (connection_list))
{
}

algo::FloydWarshall::FloydWarshall
    (const ConnectionMatrix & connection_matrix)
{
    m_distances = connection_matrix;
    size_t matrix_size = connection_matrix.size();
    m_parents = algo::createMatrix(matrix_size, matrix_size, -1);
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

algo::FloydWarshall::FloydWarshall
    (const ListOfEdges & list_of_edges)
        : FloydWarshall(
            algo::Graph::ListOfEdgesToConnectionMatrix
            (list_of_edges))
{
}

algo::FloydWarshall::WeightType 
    algo::FloydWarshall::GetDistance
        (int from, int to)

{
    return m_distances[from][to];
}

std::vector<int> 
    algo::FloydWarshall::GetDistance
        (int from)
{
    return m_distances[from];
}

std::vector<int>
    algo::FloydWarshall::GetPath
        (int from, int to)
{
   /* std::vector<int> path;
    if (from == to)
        return path;
    get_path(from, to, path);
    return path;*/
    std::vector<int> path;
    if(m_parents[from][to] == -1)
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
    algo::FloydWarshall::get_path
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
