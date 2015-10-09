/**
 * Defines the graph structures and some functions used in Micali-Vazirani
 * maximum matching algorithm.
 */
#include "adt.h"
#define INFINITY -1

typedef enum {
    // 0, 1
    MATCHED, UNMATCHED,
    //2, 3
    VISITED, UNVISITED,
    //4, 5
    CHECKED, UNCHECKED,
    //6, 7
    ERASED, UNERASED,
    //8, 9
    USED, UNUSED,
    //10, 11
    LEFT, RIGHT
} Label;

typedef struct vertex{
    //assuming vertex ids start at 0 to n-1, n being the total number of vertices
    int id;
    //used for DFS in FINDPATH
    Label visited;
    Label matched;
    //in case the vertex is matched
    struct vertex *mate;
    //used in leftdsf and rightdfs
    struct vertex *parent;
    struct edge *matched_edge;
    //ERASED or UNERASED -- used on disjoint augmenting paths
    Label status;
    //LEFT or RIGHT -- used in BLOSS-AUG
    Label side;
    //using positive numbers to denote the level, and -1 to denote infinity
    int evenlevel;
    int oddlevel;
    //id of the bloom which this vertex belongs
    int bloom;
    List *predecessors;
    List *successors;
    List *anomalies;
    //erased predecessors
    int count;
    List *neighbors;
} Vertex;

typedef struct edge{
    //for DFS in BLOSS-AUG
    Label used;
    //for DFS in FINDPATH
    Label visited;
    Label matched;
    //used when increasing the match to avoid adding edges twice
    Label checked;
    Vertex* v1;
    Vertex* v2;
    double weight;
} Edge;

typedef struct graph{
    size_t vertex_n;
    size_t edge_n;
    Vertex **v;
    Edge **e;

    Queue *blooms;
} Graph;

//Graph adt functions
Vertex* vertex_create (int id);
Edge* edge_create (Vertex *v1, Vertex *v2);
Edge* get_edge_by_vertices (Graph *G, Vertex* v1, Vertex* v2);
Graph* graph_create (size_t vertex_n, size_t edge_n);
