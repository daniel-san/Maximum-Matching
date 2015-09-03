/**
 * File with the implementation of Karp-Sipser's greedy algorithm 
 * to find a matching in a graph. Used by Chebolu et al. to develop a 
 * O(n) algorithm to find a maximum matching on a given graph.
 */
#include <stdlib.h>
#include <time.h>
#include "ks_graph.h"

void
swap_last ()
{

}

void
greedy_matching (Graph G)
{
    srand (time (NULL));

    int n;
    List* M = list_create();
    Edge *e;
    Vertex *v;
    while (G.edge_n > 0)
    {
        //Verify vertices with degree 1
        if (G.vertex1_n > 0)
        {
            n = rand() % G.vertex1_n;
            v = &G.V1[n];
            //execute this procedure when 'deleting' edges
            //this code here for vertices isn't needed, at least for now
            G.V1[n] = G.V1[G.vertex1_n - 1];
            G.V1[G.vertex1_n - 1] = *v;
            G.vertex1_n--;

        }

    }
    list_add (M, (void*) e);
}
