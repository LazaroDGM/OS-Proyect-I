#include <stdio.h>
#include <stdlib.h>
#include "snklib.h"
#include "utillib.h"

void push(Stack *s, Body b){
    Node *node;
    node = (Node*)malloc(sizeof(Node));
    node->body = b;
    node->next = s->top;
    s->top = node;
    s->count++;
}

Body peek(Stack *s){
    return s->top->body;
}

Body pop(Stack *s){
    Body body =  s->top->body;
    s->top=s->top->next;
    s->count--;
    return body;
}

void new_stack(Stack *s){
    s->count=0;
    s->top = NULL;
}