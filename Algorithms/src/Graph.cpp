#include "Graph.h"

algo::Graph::Edge::Edge(int from, int to, int weight)
    : from(from)
    , to(to)
    , weight(weight)
{}

//algo::Graph::Edge::Edge(int to, int weight)
//    : Edge(-1, to, weight)
//{
//}

algo::Graph::Edge::Edge()
    : Edge(-1,-1,-1)
{
}
