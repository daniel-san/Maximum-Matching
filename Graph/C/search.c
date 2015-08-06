#include "search.h"

void DFS(Graph g, Vertex v)
{
    Stack* stack = stack_create();
    List* neighbors;
    Element* temp;

    stack_push(stack, (void*) v);
    while(stack->stack_size > 0)
    {
        v = (Vertex) stack_pop(stack)->data;
        if (!v.visited)
        {
			v.visited = 1;
			neighbors = v.neighbors;
			temp = neighbors->head;
			while (temp != NULL)
			{
				stack_push(stack, temp->data);
				temp = temp->next;
			}

        }
    }
}

void BFS(Graph g, Vertex v)
{
	Queue* queue = queue_create();
	List* neighbors;
	Element* temp;

	queue_enqueue(queue, (void*)v);
	while(queue->queue_size > 0)
	{
		v = (Vertex) queue_dequeue(queue)->data;
		neighbors = v.neighbors;
		temp = neighbors->head;
		while (temp != NULL)
		{
			v = (Vertex) temp->data;
			if (!v.visited)
			{
				v.visited = 1;
				queue_enqueue(queue, (void*) v);

			}
			temp = temp->next;
		}
	}
}       