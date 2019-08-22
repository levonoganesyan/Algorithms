#pragma once
#include<Graph\Graph.h>
namespace algo
{

	class LCA
	{
		using ConnectionList = Graph::ConnectionList;
		using ConnectionMatrix = Graph::ConnectionMatrix;
		using ListOfEdges = Graph::ListOfEdges;
		using VertexType = Graph::VertexType;

		using VertexState = Graph::VertexState;

		void dfs(const ConnectionList& graph, int vertex);

	public:
		LCA(const Graph& graph);
		LCA(const ConnectionList& graph);
		LCA(const ConnectionMatrix& graph);
		LCA(const ListOfEdges& graph);

	};

}
