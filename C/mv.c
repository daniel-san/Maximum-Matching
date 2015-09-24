/** 
 * File with the implementation of Micali and Vazirani algorithm 
 * to find a maximum matching in a given graph. It is the fastest 
 * known algorithm for finding a maximum matching.
 */
#include <stdlib.h>
#include <time.h>
#include "mv_graph.h"

/*
 * Set some vertex attributes to default values 
 */
void
initialize_vertex (Vertex *v)
{
    v->evenlevel = v->oddlevel = INFINITY;
    v->bloom = -1;
    list_destroy (v->predecessors);
    list_destroy (v->successors);
    list_destroy (v->anomalies);

    v->predecessors = list_create();
    v->successors = list_create();
    v->anomalies = list_create();
    
    v->count = 0;
    v->status = UNERASED;
    v->visited = UNVISITED;

}
/*
 * Set some edge attributes to default values
 */
void
initialize_edge (Edge *e)
{
    e->used = UNUSED;
    e->visited = UNVISITED;
}

/*
 * Returns a list containing the exposed vertices of 
 * a graph G.
 */
List * 
get_exposed_vertices (Graph *G)
{
    int i;
    List *exposed_v = list_create();
    for (i = 0; i < G->vertex_n; i++)
    {
        if (G->v[i].matched != MATCHED)
        {
            list_add (exposed_v, (void*) &G->v[i]);
        }
    }

    return exposed_v;
}


/*
 * Function to used to setup a initial matching from the given graph
 */
List *
initial_matching (Graph *G)
{

    srand(time(NULL));
    
    List *M = list_create ();
    int n;
    int i;
    Edge *e;

    n = rand () % G->edge_n;
    /*
     * TODO: Create a function to add the edge to the matching list, 
     *       and set its vertices matched label to MATCHED.
     */
    e = &G->e[n];
    e->v1->matched = e->v2->matched = MATCHED;
    
    list_add (M, (void *) e);
    
    for (i = 0; i < n; i++)
    {
        n = rand () % G->edge_n;
        e = &G->e[n];
        //verifying if one of the vertices of the selected edge is already matched
        if ( (e->v1->matched == UNMATCHED) && (e->v2->matched == UNMATCHED) )
        {
            //if both vertices are not matched, add e to M
            e->v1->matched = e->v2->matched = MATCHED;
            list_add (M, (void *) e);
        }
    }

    return M;
}

/*
 * Subroutine SEARCH
 * Note: not treating blossoms yet
 */
Bool
search(Graph *G, List *candidates, List *bridges, int phase)
{
    int i = 0;
    Element *el;
    Vertex *v;
    //probably will become an external value
    Bool last_phase_has_augmenting_path = False;
    List *candidates_el = (List *) list_n_get(candidates, 0)->data;

    //preparing to start the first phase: Search
    List *exposed_vertices = get_exposed_vertices (G);

    //the lines below are already part of search execution
    for (el = exposed_vertices->head; el != NULL; el = el->next)
    {
        v = (Vertex *) el->data;
        v->evenlevel = 0;
        list_add (candidates_el, (void *) v);
    }

    candidates_el = (List *) list_n_get(candidates, i);
    while (!list_is_empty (candidates_el) 
           && !last_phase_has_augmenting_path)
    {
        if (i % 2 == 0)
        {
            for (el = candidates_el->head; el != NULL; el = el->next)
            {
                v = (Vertex *) el->data;
                //access unerased neighbors of v, and verify free edges between them
            }
        }
        else
        {
            for (el = candidates_el->head; el != NULL; el = el->next)
            {
                v = (Vertex *) el->data;
                if (v->bloom == -1)
                {

                }
            }
        }
    }
    

    return False;
}

List * 
matching (Graph *G)
{
    //Loop variables
    int i;
    Bool has_augmenting_path = True;
    int phase = 0;
    Vertex *v;
    List *M = initial_matching (G);
    while(has_augmenting_path)
    {
        //List of lists
        List *candidates = list_create ();
        List *bridges = list_create ();
            
        //setting the evenlevel and oddlevel of all vertices to infinity(-1)
        for (i = 0; i < G->vertex_n; i++)
        {
            initialize_vertex (&G->v[i]);
            list_add (candidates, (void *) list_create ());
            list_add (bridges, (void *) list_create ());
        }
        
        for (i = 0; i < G->edge_n; i++)
        {
            initialize_edge(&G->e[i]);
        }

        has_augmenting_path = search(G, candidates, bridges, phase);
    }
    return M;
}
