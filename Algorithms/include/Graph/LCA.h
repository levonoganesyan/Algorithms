#pragma once
#include<Graph\Graph.h>
#include<vector>
namespace algo
{

	class LCA
	{
		using ConnectionList = Graph::ConnectionList;
		using ConnectionMatrix = Graph::ConnectionMatrix;
		using ListOfEdges = Graph::ListOfEdges;
		using VertexType = Graph::VertexType;

		std::vector<int> m_time_in;
		std::vector<int> m_time_out;
		std::vector<std::vector<VertexType>> m_up;

		int timer;

		void dfs(const ConnectionList& graph, int vertex, int prev = 0);
		bool upper(int a, int b) const;
		static int greater_power_of_2(int n);

	public:
		LCA(const Graph& graph);
		LCA(const ConnectionList& graph);
		LCA(const ConnectionMatrix& graph);
		LCA(const ListOfEdges& graph);

		int Get(int a, int b) const;
	};

}
