/**
 * Definitions used in Micali-Vazirani maximum matching algorithm.
 */
#include "mv_graph.h"

typedef struct bloom{
    int id;
    Vertex* base, *left_peak, *right_peak;
    List *vertices;
} Bloom;

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
Bool bloss_aug (Graph *G, Edge *e, List *candidates, List *bridges, 
                List *M, int phase);
Bool search (Graph *G, List *candidates, List *bridges, List *M);
List * matching (Graph *G);
