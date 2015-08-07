#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char* argv[])
{
    int n = 5, i;
    struct vertex temp;
    struct graph G;
    G.v = (struct vertex*) malloc (n * sizeof(struct vertex));
    G.e = (struct edge*) malloc (n * sizeof(struct edge));

    struct vertex *vec = G.v;
    //Testing graph vertex array insertion
    for(i = 0; i < n; i++)
    {
        vec[i].id = i;
        printf("%d\n",vec[i].id);
    }
    
    //testing graph edge array insertion
    G.e[0].v1 = G.v[0]; G.e[0].v2 = G.v[1];
    G.e[1].v1 = G.v[1]; G.e[1].v2 = G.v[2];
    G.e[2].v1 = G.v[2]; G.e[2].v2 = G.v[3];
    G.e[3].v1 = G.v[3]; G.e[3].v2 = G.v[4];
    G.e[4].v1 = G.v[4]; G.e[4].v2 = G.v[0];
    for(i = 0; i < n; i++)
    {
        printf("%d --> %d\n", G.e[i].v1.id, G.e[i].v2.id);
    }

}
