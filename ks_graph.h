#include <stdlib.h>
#include "C/adt.h"


/**
 * Vertex structure
 */
typedef struct vertex
{
    int id;
    int index; //index in the vertices list (G.V)
    int degree;
    List* L; //list of Edge structures
    //List* neighbors;
}Vertex;

/**
 * Edge structure
 */
typedef struct edge
{
    //vertices index or id
    int u;
    int v;
    struct edge_repr* er;
}Edge;

/**
 * Edge representative structure
 */
typedef struct edge_repr
{
    //vertices index or id
    int u;
    int v;
    
    //position of edge (u,v) in u.L list//--
    Element *pos_u;                     //  |-> Should really be pointers?
    //position of edge(u,v) in v.L list //--
    Element *pos_v;
}Edge_repr;

/**
 * Graph structure
 */
typedef struct graph
{
    size_t vertex_n; //number of vertices
    size_t vertex1_n; //number of vertices of degree 1
    size_t edge_n; //number of edges
    Vertex *V; //vertices array -- not indexed by vertex ids
    Vertex *V1; //array of vertices of degree 1
    Edge_repr *E; //edge representatives array
}Graph;

Vertex vertex_create (int id);
void vertex_set_degree (Vertex *v); //may not be needed...
Element* search_vertex_list (Vertex v, int u_id, int v_id);
Edge edge_create (Vertex *v1, Vertex *v2);
Edge_repr edge_repr_create (Vertex *V,int u_id, int v_id);
Graph graph_create (size_t vertex_n, size_t edge_n);
