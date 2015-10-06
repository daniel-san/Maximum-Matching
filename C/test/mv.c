#include <stdlib.h>
#include <stdio.h>
#include "../mv.h"

/*Test creating a graph with the following topology
  0 ---- 1 --x-- 2 ---- 3 --x-- 4 ---- 5
*/
int
main (int argc, char* argv[])
{
    int n = 6, i;
    List *M;
    Edge *e_temp;
    Element *el;

    Graph G = graph_create (n, n - 1);

    //vertex insertion
    for(i = 0; i < n; i++)
    {
        G.v[i] = vertex_create (i);
    }
    
    //edge insertion
    G.e[0] = edge_create (&G.v[0], &G.v[1]); 
    G.e[1] = edge_create (&G.v[1], &G.v[2]);
    G.e[2] = edge_create (&G.v[2], &G.v[3]); 
    G.e[3] = edge_create (&G.v[3], &G.v[4]);
    G.e[4] = edge_create (&G.v[4], &G.v[5]);


    //simple case
    G.e[1].v1->matched = G.e[1].v2->matched = MATCHED;
    G.e[1].matched = MATCHED;
    G.e[1].v1->mate = G.e[1].v2;
    G.e[1].v2->mate = G.e[1].v1;
    G.e[1].v1->matched_edge = &G.e[1];
    G.e[1].v2->matched_edge = &G.e[1];

    G.e[3].v1->matched = G.e[3].v2->matched = MATCHED;
    G.e[3].matched = MATCHED;
    G.e[3].v1->mate = G.e[3].v2;
    G.e[3].v2->mate = G.e[3].v1;
    G.e[3].v1->matched_edge = &G.e[3];
    G.e[3].v2->matched_edge = &G.e[3];


    //M = initial_matching (&G);
    M = matching(&G);

    for (el = M->head; el != NULL; el = el->next)
    {
        e_temp = (Edge*) el->data;
        printf ("Edge %d --> %d\n", e_temp->v1->id, e_temp->v2->id);
    }

}
