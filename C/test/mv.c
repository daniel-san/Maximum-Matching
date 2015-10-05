#include <stdlib.h>
#include <stdio.h>
#include "../mv.h"


int
main (int argc, char* argv[])
{
    int n = 10, i;
    List *M;
    Edge *e_temp;
    Element *el;

    //Will be a tree graph
    Graph G = graph_create (n, n - 1);

    //vertex insertion
    for(i = 0; i < n; i++)
    {
        G.v[i] = vertex_create (i);
    }
    
    //edge insertion
    G.e[0] = edge_create (&G.v[0], &G.v[1]);
    G.e[1] = edge_create (&G.v[0], &G.v[2]);
    G.e[2] = edge_create (&G.v[2], &G.v[5]);
    G.e[3] = edge_create (&G.v[2], &G.v[6]);
    G.e[4] = edge_create (&G.v[1], &G.v[3]);
    G.e[5] = edge_create (&G.v[1], &G.v[4]);
    G.e[6] = edge_create (&G.v[3], &G.v[7]);
    G.e[7] = edge_create (&G.v[4], &G.v[8]);
    G.e[8] = edge_create (&G.v[5], &G.v[9]);

    //M = initial_matching (&G);
    M = matching(&G);

    for (el = M->head; el != NULL; el = el->next)
    {
        e_temp = (Edge*) el->data;
        printf ("Edge %d --> %d\n", e_temp->v1->id, e_temp->v2->id);
    }

}
