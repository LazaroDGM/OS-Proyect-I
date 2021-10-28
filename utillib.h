typedef struct node{
    struct body body;
    struct node *next;
}Node;

typedef struct stack{
    Node *top;
    int count;
}Stack;

typedef struct queue{
    Node *first;
    Node *last;
    int count;
}Queue;

void push(Stack *s, Body b);
Body peek_s(Stack *s);
Body pop(Stack *s);
void new_stack(Stack *s);

void enqueue(Queue *q, Body b);
Body dequeue(Queue *q);
Body peek_q(Queue *q);
void new_queue(Queue *q);