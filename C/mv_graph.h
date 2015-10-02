#include "adt.h"
#define INFINITY -1

typedef enum {
    MATCHED, UNMATCHED,
    VISITED, UNVISITED,
    ERASED, UNERASED,
    USED, UNUSED,
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
    Vertex* v1;
    Vertex* v2;
    double weight;
} Edge;

typedef struct graph{
    size_t vertex_n;
    size_t edge_n;
    Vertex* v;
    Edge* e;

    Queue *blooms;
} Graph;

typedef struct bloom{
    int id;
    Vertex* base, *left_peak, *right_peak;
    List *vertices;
} Bloom;

//Graph adt functions
Vertex vertex_create (int id);
Edge edge_create (Vertex *v1, Vertex *v2);
Edge* get_edge_by_vertices (Graph *G, Vertex* v1, Vertex* v2);
Graph graph_create (size_t vertex_n, size_t edge_n);


//Matching functions
void initialize_vertex (Vertex *v);
int vertex_level (Vertex *v);
void initialize_edge (Edge *e);
List * get_free_edges (Graph *G);
List * get_exposed_vertices (Graph *G);
List * initial_matching (Graph *G);
void bloom_create (Graph *G, Edge *bridge, int phase,
                   List *candidates, List *bridges,
                   List *bloom_vertices, Vertex *DCV);
void erase (List *Y);
Vertex * base_p (Vertex *v, Queue *blooms);
Queue * open (Graph *g, Vertex *x);
Queue * findpath (Graph *G, Vertex *high, Vertex *low, Bloom *B);
Bool left_dfs (Graph *G, Vertex *s, Vertex *vl, Vertex *vr, 
                Vertex *DCV, Vertex *barrier, List *bloom_vertices);
void right_dfs (Graph *G, Vertex *vl, Vertex *vr, 
                Vertex *DCV, Vertex *barrier, List *bloom_vertices);
void bloss_aug (Graph *G, Edge *e, List *candidates, List *bridges, 
                List *M, int phase);
Bool search (Graph *G, List *candidates, List *bridges, List *M);
List * matching (Graph *G);
