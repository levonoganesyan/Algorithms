#pragma once
#include<Graph/Graph.h>
namespace algo
{
	class ChromaticNumber
	{
	private:

		using ConnectionList = Graph::ConnectionList;
		using ConnectionMatrix = Graph::ConnectionMatrix;
		using ListOfEdges = Graph::ListOfEdges;
		using Edge = Graph::Edge;
		using Color = Graph::Color;

		std::vector<Color> m_colors;
		int m_chromatic_number;

		void dfs(const ConnectionList& graph, int v);

	public:
		ChromaticNumber(const Graph& graph);
		ChromaticNumber(const ConnectionList& graph);
		ChromaticNumber(const ConnectionMatrix& graph);
		ChromaticNumber(const ListOfEdges& graph);
		std::vector<Color> GetColors() const;
		int GetNumber() const;
	};
}