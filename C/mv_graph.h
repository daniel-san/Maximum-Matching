#include "adt.h"
#define INFINITY -1

typedef enum {MATCHED, UNMATCHED, ERASED, EMPTY} Label;

typedef struct vertex{
    //assuming vertex ids start at 0 to n-1, n being the total number of vertices
    int id;
    int visited;
    Label matched;
    //using positive numbers to denote the level, and -1 to denote infinity
    int evenlevel;
    int oddlevel;
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

//Graph adt functions
Vertex vertex_create (int id);
Edge edge_create (Vertex *v1, Vertex *v2);
Graph graph_create (size_t vertex_n, size_t edge_n);

//Matching functions
List * initial_matching (Graph *G);
List * matching (Graph *G);
