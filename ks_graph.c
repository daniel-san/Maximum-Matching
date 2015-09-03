#include "ks_graph.h"

/**
 * Create a vertex and initialize some of its attributes
 */
Vertex
vertex_create (int id)
{
    Vertex v;
    v.id = id;
    v.degree = 0;
    v.L = list_create ();
    
    return v;
}

/**
 * Set the degree of a given vertex
 */
void
vertex_set_degree (Vertex *v)
{
    v->degree = v->L->list_size;
}

/**
 * Find the vertices of V that have degree 1, and add them to 
 * the array V1. Also updates the index attribute at each vertex
 */
void degree1_vertices (Vertex *V, Vertex *V1, size_t vertex_n)
{
    int v1_count = 0, i, j = 0;
    for (i = 0; i < vertex_n; i++)
    {
        if (V[i].degree == 1)
        {
            v1_count++;
            V[i].index = i;
        }
    }

    V1 = (Vertex*) malloc (v1_count * sizeof (Vertex));

    for (i = 0; i < vertex_n; i++)
    {
        if (V[i].degree == 1)
        {
            V1[j] = V[i];
            j++;
        }
    }
}

//probably will be modified, if i misunderstood what the paper said
/**
 * Search for the edge (u,v) in the linked list v.L, 
 * and returns the list element if found
 */
Element *
search_vertex_list (Vertex v, int u_id, int v_id)
{
    Edge *e;
    Element *el; //element that will be returned
    Element *L = v.L->head;
    while(L != NULL)
    {
        e = (Edge*) L->data;
        if(e->u == u_id && e->v == v_id)
        {
            el = L;
            break;
        }
        L = L->next;
    }

    return el;
}

/**
 * Create a edge and initialize some of its attributes
 */
Edge
edge_create (Vertex *v1, Vertex *v2)
{
    Edge e;
    e.u = v1->id;
    e.v = v2->id;

    list_add (v1->L, (void*) &e);
    list_add (v2->L, (void*) &e);

    return e;
}

/**
 * Creates a edge representative struct and initialize some of its attributes
 */
Edge_repr
edge_repr_create (Vertex *V, int u_id, int v_id)
{
    Edge *e;
    Edge_repr er;
    er.u = u_id;
    er.v = v_id;
    er.pos_u = search_vertex_list (V[u_id], u_id, v_id);
    er.pos_v = search_vertex_list (V[v_id], u_id, v_id);

    e = (Edge*) er.pos_u->data;
    e->er = &er;
    
    e = (Edge*) er.pos_v->data;
    e->er = &er;

    return er;
}

/**
 * Creates a graph, with vertex_n vertices and edge_n edges
 */
Graph
graph_create (size_t vertex_n, size_t edge_n)
{
    Graph G; 
    G.vertex_n = vertex_n;
    G.edge_n = edge_n;
    G.vertex1_n = 0;

    G.V = (Vertex*) malloc (vertex_n * sizeof (Vertex));
    G.E = (Edge_repr*) malloc (edge_n * sizeof (Edge_repr));
    return G;
}
