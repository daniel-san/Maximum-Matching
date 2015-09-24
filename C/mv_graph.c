#include <stdlib.h>
#include "mv_graph.h"

Vertex
vertex_create (int id)
{
    Vertex v;
    v.id = id;
    v.visited = UNVISITED;
    v.matched = UNMATCHED;
    return v;
}

Edge
edge_create (Vertex *v1, Vertex *v2)
{
    Edge e;
    e.v1 = v1;
    e.v2 = v2;
    return e;
}

Graph
graph_create (size_t vertex_n, size_t edge_n)
{
    Graph g;
    g.vertex_n = vertex_n;
    g.edge_n = edge_n;
    g.v = (Vertex*) malloc (vertex_n * sizeof (Vertex));
    g.e = (Edge*) malloc (edge_n * sizeof (Edge));

    return g;
}