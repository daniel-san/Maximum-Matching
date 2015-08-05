#include "queue_stack.h"
#include <stdlib.h>

Stack* stack_create()
{
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if (stack != NULL)
    {
        stack->stack_size = 0;
        stack->top = NULL;
    }

    return stack;
}

void stack_push(Stack* s, void* data)
{
    Element* stack_top = s->top;
    Element* new_element = (Element*) malloc(sizeof(Element));
    if (new_element != NULL)
    {
        new_element->data = data;
        s->top = new_element;
        new_element->next = stack_top;
        s->stack_size++;
    }
}

Element* stack_pop(Stack* s)
{
    Element* stack_top = s->top;
    if (stack_top != NULL)
    {
        s->top = stack_top->next;
        s->stack_size--;
    }

    return stack_top;
}

//queue functions

Queue* queue_create()
{
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if (queue != NULL)
    {
        queue->queue_size = 0;
        queue->first = queue->last = NULL;
    }

    return queue;
}

void queue_enqueue(Queue* q, void* data)
{
    Element* new_element = (Element*) malloc(sizeof(Element));
    if (new_element != NULL)
    {
        new_element->data = data;
        if ((q->first == NULL) && (q->last == NULL))
        {
            q->first = q->last = new_element;
        }
        else
        {
            q->last->next = new_element;
            q->last = new_element;
        }
        q->queue_size++;
    }
}

Element* queue_dequeue(Queue* q)
{
    Element* queue_first = q->first;

    if (q->first == q->last)
    {
        q->first = q->last = NULL;
    }
    else
    {
        q->first = queue_first->next;
    }
    q->queue_size--;

    return queue_first;
}
