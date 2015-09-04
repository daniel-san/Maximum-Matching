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

            //deleting the selected vertex from V1
            G.V1[n] = G.V1[G.vertex1_n - 1];
            G.V1[G.vertex1_n - 1] = *v;
            G.vertex1_n--;

            e = (Edge*) v->L->head->data;

            //deleting the only edge of v from G.E and updating edges index
            n = e->er->index;
            G.E[n] = G.E[G.edge_n - 1];
            G.E[G.edge_n - 1] = *e->er;
            e->er->index = G.edge_n - 1;
            G.E[n].index = n;
            G.edge_n--;

        }
        else
        {
            //section of code for when there are no more vertex of degree 1
            
        }

    }

}
