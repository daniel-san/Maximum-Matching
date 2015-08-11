#include <stdio.h>
#include <stdlib.h>
//#include "graph.h"
#include "search.h"
int main(int argc, char* argv[])
{
    int n = 5, i;
    Element* e_temp;
    Vertex* v_temp;

    Graph G = graph_create(n,n);

    //Testing graph vertex array insertion
    for(i = 0; i < n; i++)
    {
        G.v[i] = vertex_create(i);
        printf("Vertex %d\n",G.v[i].id);
    }
    
    //testing graph edge array insertion
    G.e[0] = edge_create(&G.v[0], &G.v[1]);
    G.e[1] = edge_create(&G.v[1], &G.v[2]);
    G.e[2] = edge_create(&G.v[2], &G.v[3]);
    G.e[3] = edge_create(&G.v[3], &G.v[4]);
    G.e[4] = edge_create(&G.v[4], &G.v[0]);

    for(i = 0; i < n; i++)
    {
        printf("%d --> %d\n", G.e[i].v1->id, G.e[i].v2->id);
    }

    //testing accessing vertex neighbors
    for (i = 0; i < n; i++)
    {
        printf("Vertex id %d\n",G.v[i].id);
        e_temp = G.v[i].neighbors->head;
        while (e_temp != NULL)
        {
            v_temp = (Vertex*) e_temp->data;
            printf("\t Neighbor Id %d\n", v_temp->id);

            e_temp = e_temp->next;
        }
    }

    //testing DFS and BFS
    //DFS(&G.v[0]);
    //BFS(&G.v[0]);
}
