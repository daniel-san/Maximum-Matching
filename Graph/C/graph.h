#include "adt.h"

typedef struct vertex{
    int id;
    int visited;
    List* neighbors;
} Vertex;

typedef struct edge{
    Vertex* v1;
    Vertex* v2;
    double weight;
} Edge;

typedef struct graph{
    size_t vertex_n;
    size_t edge_n;
    Vertex* v;
    Edge* e;
} Graph;

Vertex vertex_create(int id);
Edge edge_create(Vertex* v1, Vertex* v2);
Graph graph_create(size_t vertex_n, size_t edge_n);
