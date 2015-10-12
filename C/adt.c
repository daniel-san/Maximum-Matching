/**
 * Implementation of the adt functions used through the library
 */
#include <stdlib.h>
#include <stdio.h>
#include "adt.h"

Stack *
stack_create ()
{
    Stack *stack = (Stack*) malloc (sizeof (Stack));
    if (stack != NULL)
    {
        stack->top = NULL;
        stack->stack_size = 0;
    }

    return stack;
}

void
stack_push (Stack *s, void *data)
{
    Element* stack_top = s->top;
    Element* new_element = (Element*) malloc (sizeof (Element));
    if (new_element != NULL)
    {
        new_element->data = data;
        s->top = new_element;
        new_element->next = stack_top;
        s->stack_size++;
    }
}

Element *
stack_pop (Stack* s)
{
    Element* stack_top = s->top;
    if (stack_top != NULL)
    {
        s->top = stack_top->next;
        s->stack_size--;
    }
    return stack_top;
}

Bool
stack_is_empty (Stack *s)
{
    return (s->top == NULL);
}

void
stack_destroy (Stack *s)
{
    Element *e;
    if (s != NULL)
    {
        while(s->stack_size > 0)
        {
            e = stack_pop(s);
            free (e);
        }
    }
    free (s);
}

//queue functions

Queue *
queue_create ()
{
    Queue *queue = (Queue*) malloc (sizeof (Queue));
    if (queue != NULL)
    {
        queue->first = queue->last = NULL;
        queue->queue_size = 0;
    }

    return queue;
}

void
queue_enqueue (Queue *q, void *data)
{
    Element *new_element = (Element*) malloc (sizeof(Element));
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

Element *
queue_dequeue (Queue *q)
{
    Element *queue_first = q->first;

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

/*
 * Iterate through the queue, with the first element being treated 
 * as element 0, and the last as queue_size - 1
 */
Element *
queue_n_get (Queue *q, int n)
{
    int i = 0;
    Element *el = q->first;
    while (i < n)
    {
        el = el->next;
        i++;
    }

    return el;
}

Bool
queue_is_empty (Queue *q)
{
    return (q->first == NULL && q->last == NULL);
}

void
queue_destroy (Queue *q)
{
    Element *e;
    if (q != NULL)
    {
        while (q->queue_size > 0)
        {
            e = queue_dequeue(q);
            free (e);
        }
    }
    free (q);
}

//list functions

List *
list_create ()
{
    List *list = (List*) malloc (sizeof (List));
    if (list != NULL)
    {
        list->head = NULL;
        list->list_size = 0;
    }
    return list;
}

void
list_add (List *l, void *data)
{
    Element *new_element = (Element*) malloc (sizeof (Element));
    if (new_element != NULL)
    {
        new_element->data = data;
        if (l->head == NULL)
        {
            l->head = new_element;
        }
        else
        {
            new_element->next = l->head;
            l->head = new_element;
        }
        l->list_size++;
    }   
}

Element *
list_pop (List *l)
{
    Element* list_head = l->head;
    if (list_head != NULL)
    {
        l->head = list_head->next;
        l->list_size--;
    }
    return list_head; 
}


/*
 * Iterate through the list, with the first element being treated 
 * as element 0, and the last as list_size - 1
 */
Element *
list_n_get (List *l, int n)
{
    int i = 0;
    Element *el = l->head;
    while (i < n)
    {
        el = el->next;
        i++;
    }

    return el;
}

Bool
list_is_empty (List *l)
{
    return (l->head == NULL); 
}

void
list_delete (List *l, Element *e)
{
    Element *temp;
    if (l != NULL && e != NULL)
    {
        temp = l->head;
        while (temp->next != e)
            temp = temp->next;

        temp->next = e->next;
        l->list_size--;
        free (e);
    }
}

void
list_destroy (List *l)
{
    Element *e;
    if (l != NULL)
    {
        while (l->list_size > 0)
        {
            e = list_pop (l);
            free (e);
        }
    }
    free (l);
}
