#include "ks_graph.h"

Vertex
vertex_create (int id)
{
    Vertex v;
    v.id = id;
    v.degree = 0;
    v.L = list_create ();
    
    return v;
}

void
vertex_set_degree (Vertex *v)
{
    v->degree = v->L->list_size;
}

//probably will be modified, if i misunderstood what the paper said
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

Edge
edge_create (Vertex *v1, Vertex *v2)
{
    Edge e;
    e.u = v1->id;
    e.v = v2->id;

    list_add (v1->L, (void*) &e);
    list_add (v2->L, (void*) &e);

    /**(TODO)
     * - pass the array with all vertices of the graph to the function.
     * - maybe extend existing Element struct to have a attribute 
     *   that indicates its index in the linked list/queue/stack.
     */
    //e.er = edge_repr_create()
    return e;
}

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


    return er;
}

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
