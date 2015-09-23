/** 
 * File with the implementation of Micali and Vazirani algorithm 
 * to find a maximum matching in a given graph. It is the fastest 
 * known algorithm for finding a maximum matching.
 */
#include <stdlib>
#include <time.h>
#include "graph.h"
#include "adt.h"

List *
initial_matching (Graph G)
{
    
    List *M = list_create ();
    int n,m;
    int i;
    Edge *e;
    Vertex *v;

    n = rand () % G.edge_n;
    e = &G.e[n];
    list_add (M, (void *) e);

    for (i = 0; i < n; i++)
    {
        n = rand () % G.edge_n;
        e = &G.e[n];
        //verifying if one of the vertices of the selected edge is already matched
        if (!e->v1->matched && !e->v2->matched)
        {
            //if both vertices are not matched, add e to M
            list_add (M, (void *) e);

        }
    }

    return M;
}