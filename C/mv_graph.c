#include <stdlib.h>
#include "mv_graph.h"

Vertex
vertex_create (int id)
{
    Vertex v;
    v.id = id;
    v.visited = UNVISITED;
    v.matched = UNMATCHED;
    v.predecessors = list_create();
    v.successors = list_create();
    v.anomalies = list_create();
    v.neighbors = list_create();
    v.count = 0;
    return v;
}

Edge
edge_create (Vertex *v1, Vertex *v2)
{
    Edge e;
    e.v1 = v1;
    e.v2 = v2;
    e.matched = UNMATCHED;
    list_add (v1->neighbors, (void *) v2);
    list_add (v2->neighbors, (void *) v1);
    return e;
}

Edge* get_edge_by_vertices (Graph *G, Vertex* v1, Vertex* v2)
{
    //search the list of edges for the edge made from these 2 vertices
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
