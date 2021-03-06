#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph_generator.h"

Graph
random_graph (size_t n, int p)
{
    srand(time(NULL));
    
    int i, j;
    Graph G;
    List *v1_list = list_create();
    List *v2_list = list_create();

    G.vertex_n = n;
    G.edge_n = 0;
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
                G.edge_n++;
                list_add(v1_list,&G.v[i]);
                list_add(v2_list,&G.v[j]);
            }
        }
    }
    
    G.e = (Edge*) malloc (G.edge_n * sizeof (Edge));

    for (i = 0; i < G.edge_n; i++)
    {
        G.e[i] = edge_create ( (Vertex*) list_pop (v1_list)->data, 
                               (Vertex*) list_pop (v2_list)->data);
    }

    return G;

}
