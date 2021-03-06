/**
 * Code for abstract data type structs used through the library
 */

typedef enum{
    False, True
} Bool;

/**
 * Basic element
 * TODO: Verify if it's good to add an extra attribute 
 * that says the index of that element in the stack/queue/list.
 */
typedef struct element
{
    void *data;
    struct element* next;
} Element;

//stack struct
typedef struct stack
{
    size_t stack_size;
    Element *top;
} Stack;

//queue struct
typedef struct queue
{
    size_t queue_size;
    Element *first;
    Element *last;
} Queue;

//linked list struct
typedef struct list
{
	size_t list_size;
	Element *head;
} List;

/*
 * TODO: add empty verification functions
 */

//stack functions
Stack* stack_create ();
void stack_push (Stack *s, void *data);
Element* stack_pop (Stack *s);
void stack_destroy (Stack *s);

//queue functions
Queue* queue_create ();
void queue_enqueue (Queue *q, void *data);
Element* queue_dequeue (Queue *q);
Element* queue_n_get (Queue *q, int n);
Bool queue_is_empty (Queue *q);
void queue_destroy (Queue *q);

//list functions
List* list_create ();
void list_add (List *l, void *data);
Element* list_pop (List *l);
Element* list_n_get (List *l, int n); //does not delete the element from l
Bool list_is_empty (List *l);
void list_delete (List *l, Element* e);
void list_destroy (List *l);
