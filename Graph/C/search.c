#include <stdlib.h>
#include "search.h"

void DFS(Vertex v)
{
    Stack* stack = stack_create();
    Vertex* v_temp;
    List* neighbors;
    Element* temp;

    stack_push(stack, (void*) &v);
    while(stack->stack_size > 0)
    {
        temp = stack_pop(stack);
        v_temp = (Vertex*) temp->data;
        //free(temp);

        if (!v_temp->visited)
        {
            v_temp->visited = 1;
            neighbors = v_temp->neighbors;
            temp = neighbors->head;
            while (temp != NULL)
            {
                stack_push(stack, temp->data);
                temp = temp->next;
            }

        }
    }
}

void BFS(Vertex v)
{
    Queue* queue = queue_create();
    Vertex* v_temp;
    List* neighbors;
    Element* temp;

    queue_enqueue(queue, (void*)&v);
    while(queue->queue_size > 0)
    {
        temp = queue_dequeue(queue);
        v_temp = (Vertex*) temp->data;
        //free(temp); 

        neighbors = v.neighbors;
        temp = neighbors->head;
        while (temp != NULL)
        {
            v_temp = (Vertex*) temp->data;
            if (!v_temp->visited)
            {
                v_temp->visited = 1;
                queue_enqueue(queue, (void*) v_temp);

            }
            temp = temp->next;
        }
    }
}       
