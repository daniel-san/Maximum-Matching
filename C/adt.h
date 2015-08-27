//Code for abstract data type structs used through the library

//Rough implementation draft -- Expect improvements/changes in code and file structure

// Basic element
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

//stack functions
Stack* stack_create ();
void stack_push (Stack *s, void *data);
Element* stack_pop (Stack *s);
void stack_destroy (Stack *s);

//queue functions
Queue* queue_create ();
void queue_enqueue (Queue *q, void *data);
Element* queue_dequeue (Queue *q);
void queue_destroy (Queue *q);

//list functions
List* list_create ();
void list_add (List *l, void *data);
Element* list_pop (List *l);
void list_destroy (List *l);
