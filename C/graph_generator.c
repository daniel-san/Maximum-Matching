#include <stdlib.h>
#include <time.h>
#include "adt.h"
#include "graph_generator.h"

Graph
random_graph (size_t n, int p)
{
    srand(time(NULL));
    
    int i, j;
    Edge e;
    Graph G;
    List *edge_list = list_create();

    G.vertex_n = n;
    G.v = (Vertex*) malloc (n * sizeof (Vertex));

    for (i = 0; i < n; i++)
    {
        G.v[i] = vertex_create(i);
    }

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if ( (rand() % 100) < p)
            {
                e = edge_create(&G.v[i], &G.v[j]);
                list_add(edge_list, (void*) &e);
            }
        }
    }
    
    G.edge_n = edge_list->list_size;
    G.e = (Edge*) malloc (G.edge_n * sizeof (Edge));

    for (i = 0; i < G.edge_n; i++)
    {
        G.e[i] = * (Edge*) list_pop (edge_list);
    }

    return G;

}
