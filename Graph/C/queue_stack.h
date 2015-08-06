//Code for Stack and Queue structs used on DFS and BFS

//Rough implementation draft -- Expect improvements/changes in code and file structure

// Basic element
typedef struct element
{
    void* data;
    struct element* next;
} Element;

//stack struct
typedef struct stack
{
    size_t stack_size = 0;
    Element *top;
} Stack;

//queue struct
typedef struct queue
{
    size_t queue_size = 0;
    Element *first;
    Element *last;
} Queue;

//linked list struct
typedef struct list
{
	size_t list_size = 0;
	Element* head;
} List;

//stack functions
Stack* stack_create();
void stack_push(Stack* s, void* data);
Element* stack_pop(Stack* s);

//queue functions
Queue* queue_create();
void queue_enqueue(Queue* q, void* data);
Element* queue_dequeue(Queue* q);

//list functions
List* list_create();
void list_add(List* l, void* data);
//Element* list_delete();