#include "Graph\ChromaticNumber.h"
#include "Defines.h"
namespace algo
{
	void ChromaticNumber::dfs(const ConnectionList& graph, int v)
	{
		if (m_colors[v] != -1)
		{
			return;
		}
		std::vector<Color> used_colors;
		for (int i = 0; i < graph[v].size(); ++i)
		{
			int to = graph[v][i].to;
			if (m_colors[to] != -1)
			{
				used_colors.push_back(m_colors[to]);
			}
		}
		so(used_colors);
		int color = -1;
		for (int i = 0; i < used_colors.size(); ++i)
		{
			if (used_colors[i] != i)
			{
				color = i;
				break;
			}
		}
		if (color == -1)
		{
			color = used_colors.size();
		}
		m_colors[v] = color;
		for (int i = 0; i < graph[v].size(); ++i)
		{
			int to = graph[v][i].to;
			dfs(graph, to);
		}
	}

	ChromaticNumber::ChromaticNumber(const Graph& graph)
		: ChromaticNumber(graph.AsConnectionList())
	{
	}

	ChromaticNumber::ChromaticNumber(const ConnectionList& graph)
		: m_colors(graph.size(), -1)
		, m_chromatic_number(0)
	{
		for (int i = 0; i < graph.size(); ++i)
		{
			if (m_colors[i] == -1)
			{
				dfs(graph, i);
			}
		}
		m_chromatic_number = *std::max_element(m_colors.begin(), 
											   m_colors.end()) + 1;
	}

	ChromaticNumber::ChromaticNumber(const ConnectionMatrix& graph)
		: ChromaticNumber(Graph::CM2CL(graph))
	{
	}

	ChromaticNumber::ChromaticNumber(const ListOfEdges& graph)
		: ChromaticNumber(Graph::LOE2CL(graph))
	{
	}
	std::vector<ChromaticNumber::Color> ChromaticNumber::GetColors() const
	{
		return m_colors;
	}
	int ChromaticNumber::GetNumber() const
	{
		return m_chromatic_number;
	}
}