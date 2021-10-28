typedef struct node{
    struct body body;
    struct node *next;
}Node;

typedef struct stack{
    Node *top;
    int count;
}Stack;

void push(Stack *s, Body b);
Body peek(Stack *s);
Body pop(Stack *s);
void new_stack(Stack *s);