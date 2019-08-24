#pragma once
#include<Graph/Graph.h>

namespace algo
{
	class Bridges
	{
	private:

		using ConnectionList = Graph::ConnectionList;
		using ConnectionMatrix = Graph::ConnectionMatrix;
		using ListOfEdges = Graph::ListOfEdges;
		using Edge = Graph::Edge;

		std::vector<int> m_time_in;
		std::vector<int> m_time_out;
		std::vector<int> m_f_up;
		std::vector<int> m_used;
	
		int m_timer;

		std::vector<Edge> m_bridges;

		void dfs(const ConnectionList& graph, int v, int p = -1);

	public:
		Bridges(const Graph& graph);
		Bridges(const ConnectionList& graph);
		Bridges(const ConnectionMatrix& graph);
		Bridges(const ListOfEdges& graph);
		std::vector<Edge> Get() const;
	};
}
