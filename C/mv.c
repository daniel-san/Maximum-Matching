/** 
 * File with the implementation of Micali and Vazirani algorithm 
 * to find a maximum matching in a given graph. It is the fastest 
 * known algorithm for finding a maximum matching.
 */
#include <stdlib.h>
#include <time.h>
#include "mv_graph.h"

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
    e->v1->matched = e->v2->matched =  MATCHED;
    
    list_add (M, (void *) e);
    
    for (i = 0; i < n; i++)
    {
        n = rand () % G->edge_n;
        e = &G->e[n];
        //verifying if one of the vertices of the selected edge is already matched
        if ( (e->v1->matched == UNMATCHED) && (e->v2->matched == UNMATCHED) )
        {
            //if both vertices are not matched, add e to M
            e->v1->matched = e->v2->matched =  MATCHED;
            list_add (M, (void *) e);
        }
    }

    return M;
}

/*
 * Subroutine SEARCH
 */
void 
search()
{

}

List * 
matching (Graph *G)
{
    //Loop variables
    int i;
    Element *el;

    Vertex *v;
    List *M = initial_matching (G);
    //preparing to start the first phase: Search
    List *exposed_vertices = get_exposed_vertices (G);
    
    //setting the evenlevel and oddlevel of all vertices to infinity(-1)
    for (i = 0; i < G->vertex_n; i++)
    {
        G->v[i].evenlevel = G->v[i].oddlevel = INFINITY; 
    }
    
    //the lines below are already part of search execution
    for (el = exposed_vertices->head; el != NULL; el = el->next)
    {
        v = (Vertex *) el->data;
        v->evenlevel = 0;
    }
    
    search();
    
    return M;
}
