#include<Graph/CutPoints.h>

namespace algo
{
	void CutPoints::dfs(const ConnectionList& graph, int v, int p)
	{
		m_used[v] = true;
		m_time_in[v] = m_f_up[v] = ++m_timer;

		int childs = 0;
		for (int i = 0; i < graph[v].size(); ++i)
		{
			int to = graph[v][i].to;
			if (to == p)
			{
				continue;
			}
			if (m_used[to])
			{
				m_f_up[v] = min(m_f_up[v], m_time_in[to]);
			}
			else
			{
				dfs(graph, to, v);
				m_f_up[v] = min(m_f_up[v], m_f_up[to]);
				if (m_f_up[to] >= m_time_in[v] && p != -1)
				{
					m_cut_points.push_back(v);
				}
				++childs;
			}
		}
		if (p == -1 && childs > 1)
		{
			m_cut_points.push_back(v);
		}
	}

	CutPoints::CutPoints(const Graph& graph)
		: CutPoints(graph.AsConnectionList())
	{
	}

	CutPoints::CutPoints(const ConnectionList& graph)
		: m_timer(0)
		, m_time_in(graph.size())
		, m_used(graph.size())
		, m_f_up(graph.size())
	{
		dfs(graph);
		std::sort(m_cut_points.begin(), m_cut_points.end());
		auto iter = std::unique(m_cut_points.begin(), m_cut_points.end());
		m_cut_points.erase(iter, m_cut_points.end());
		
	}

	CutPoints::CutPoints(const ConnectionMatrix& graph)
		: CutPoints(Graph::CM2CL(graph))
	{
	}

	CutPoints::CutPoints(const ListOfEdges& graph)
		: CutPoints(Graph::LOE2CL(graph))
	{
	}
	std::vector<CutPoints::VertexType> CutPoints::Get() const
	{
		return m_cut_points;
	}
}