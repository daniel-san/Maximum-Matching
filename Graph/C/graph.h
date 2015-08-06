#include <math.h>

typedef struct vertex{
    int id;
    int visited = 0;
    //List* neighbors;
} Vertex;

typedef struct edge{
    struct vertex v1;
    struct vertex v2;
    double weight;
} Edge;

typedef struct graph{
    struct vertex* v;
    struct edge* e;
} Graph;

double weight(Vertex v1, Vertex v2);
