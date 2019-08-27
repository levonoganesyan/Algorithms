#include<Graph/PruferCode.h>
#include<set>
namespace algo
{
    PruferCode::PruferCode()
    {
    }
    std::vector<int> PruferCode::Encode(const Graph& graph)
    {
        if (!graph.isTree())
        {
            return {};
        }
        auto edges = graph.AsListOfEdges();
        Graph::NormalizeListOfEdges(edges);
        
    }
    Graph PruferCode::Decode(const std::vector<int>& code)
    {
        return Graph(Graph::ConnectionList{ {} });
    }
}