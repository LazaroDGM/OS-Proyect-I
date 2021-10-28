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

Body peek_s(Stack *s){
    return s->top->body;
}

Body pop(Stack *s){
    Body body =  s->top->body;
    Node *node = s->top;
    s->top=s->top->next;
    free(node);
    s->count--;
    return body;
}

void new_stack(Stack *s){
    s->count=0;
    s->top = NULL;
}

void enqueue(Queue *q, Body b){
    Node *node;
    node = (Node*)malloc(sizeof(Node));
    node->body = b;
    node->next = NULL;
    if(q->first==NULL){
        q->first = node;
    }else{
        q->last->next=node;
    }
    q->last = node;
    q->count++;
}

Body dequeue(Queue *q){
    Body body =  q->first->body;
    Node *node = q->first;
    q->first=q->first->next;
    free(node);
    q->count--;
    return body;
}

Body peek_q(Queue *q){
    return q->first->body;
}

void new_queue(Queue *q){
    q->count=0;
    q->first = q->last = NULL;    
}