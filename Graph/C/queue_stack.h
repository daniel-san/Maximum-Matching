//Code for Stack and Queue structs used on DFS and BFS

//Rough implementation draft -- Expect improvements/changes in code and file structure

// Stack/Queue basic element
typedef struct element
{
    void* data;
    struct element* next;
} Element;

typedef struct stack
{
    size_t stack_size;
    Element *top;
} Stack;

typedef struct queue
{
    size_t queue_size;
    Element *first;
    Element *last;
} Queue;

//stack functions
Stack* stack_create();
void stack_push(Stack* s, void* data);
Element* stack_pop(Stack* s);

//queue functions
Queue* queue_create();
void queue_enqueue(Queue* q, void* data);
Element* queue_dequeue(Queue* q);
