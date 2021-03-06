#include <stdlib.h>
#include <stdio.h>
#include "../graph_generator.h"

int
main (int argc, char* argv[])
{
    Graph g;
    int i;
    int n = 10;
    int p = 60;
    /**
     * create a random graph with 10 nodes, with 60% chance of creating an 
     * edge between 2 nodes
     */
    g = random_graph(n, p);
    printf("Created edges: %d\n", g.edge_n);

    for (i = 0; i < g.edge_n; i++)
    {
        printf ("%d --> %d\n", g.e[i].v1->id, g.e[i].v2->id);
    }
    
    return 0;
}
