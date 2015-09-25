#include <stdlib.h>
#include <stdio.h>
#include "../adt.h"


int
main (int argc, char* argv[])
{
    int n = 10, i;
    Element *el;
    List *l = list_create();

    for (i = 0; i < n; i++)
    {
        list_add (l, (void *) i);
    }

    for (el = l->head; el != NULL; el = el->next)
    {
        printf ("%d\n", (int) el->data);
    }
    
    list_destroy(l);
}
