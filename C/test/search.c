#include <stdio.h>
#include <stdlib.h>
#include "../graph.h"

void
DFS (Vertex *v)
{
    Stack *stack = stack_create ();
    Vertex *v_temp;
    List *neighbors;
    Element *temp;
    
    stack_push(stack, (void*) v);
    while(stack->stack_size > 0)
    {
        temp = stack_pop(stack);
        v_temp = (Vertex*) temp->data;

        if (v_temp->visited == 0)
        {
            v_temp->visited = 1;
            printf ("\tVertex: %d\n", v_temp->id);
            neighbors = v_temp->neighbors;
            temp = neighbors->head;
            while (temp != NULL)
            {
                stack_push (stack, temp->data);
                temp = temp->next;
            }
        }
    }
}

void
BFS (Vertex *v)
{
    Queue *queue = queue_create ();
    Vertex *v_temp;
    List *neighbors;
    Element *temp;
    
    queue_enqueue (queue, (void*) v);
    while (queue->queue_size > 0)
    {
        temp = queue_dequeue (queue);
        v_temp = (Vertex*) temp->data;

        if (v_temp->visited == 0)
        {
            v_temp->visited = 1;
            printf ("\tVertex: %d\n", v_temp->id);
            neighbors = v_temp->neighbors;
            temp = neighbors->head;
            while (temp != NULL)
            {
                queue_enqueue (queue, temp->data);
                temp = temp->next;
            }

        }
    }
}

//Testing functions with a graph with the following topology
//          0
//        /   \
//       4    1
//       |    |
//       3----2
void
test_ring()
{
    int n = 5, i;
    Element *e_temp;
    Vertex *v_temp;

    Graph G = graph_create (n,n);

    G.e[0] = edge_create (&G.v[0], &G.v[1]);
    G.e[1] = edge_create (&G.v[1], &G.v[2]);
    G.e[2] = edge_create (&G.v[2], &G.v[3]);
    G.e[3] = edge_create (&G.v[3], &G.v[4]);
    G.e[4] = edge_create (&G.v[4], &G.v[0]);

    //testing DFS and BFS
    printf("\nDFS:\n");
    DFS(&G.v[0]);
    
    //resetting visited variable to 0
    for (i = 0; i < n; i++)
    {
        G.v[i].visited = 0;
    }

    printf("\nBFS:\n");
    BFS(&G.v[0]);

}

//Testing functions with a graph with the following topology
//         0
//       /   \
//      1    2
//     / \  / \
//     3 4  5 6
//     | |  |
//     7 8  9
void
test_tree()
{
    int n = 10, i;
    Element *e_temp;
    Vertex *v_temp;

    Graph G = graph_create (n,n);

    G.e[0] = edge_create (&G.v[0], &G.v[1]);
    G.e[1] = edge_create (&G.v[0], &G.v[2]);
    G.e[2] = edge_create (&G.v[2], &G.v[5]);
    G.e[3] = edge_create (&G.v[2], &G.v[6]);
    G.e[4] = edge_create (&G.v[1], &G.v[3]);
    G.e[5] = edge_create (&G.v[1], &G.v[4]);
    G.e[6] = edge_create (&G.v[3], &G.v[7]);
    G.e[7] = edge_create (&G.v[4], &G.v[8]);
    G.e[8] = edge_create (&G.v[5], &G.v[9]);
    
    //testing DFS and BFS
    printf("\nDFS:\n");
    DFS(&G.v[0]);

    //resetting visited variable to 0
    for (i = 0; i < n; i++)
    {
        G.v[i].visited = 0;
    }

    printf("\nBFS:\n");
    BFS(&G.v[0]);
}

int
main (int argc, char* argv[])
{
    test_ring ();
    printf("\n\n----------------------------------\n");
    test_tree ();
}
