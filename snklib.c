#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snklib.h"

void moveTo(struct map *m, struct snake *s, int new_x, int new_y)
{
    if(s->grow_count == 0) 
    {
        m->grid[s->body[s->tail].y][s->body[s->tail].x] = VOID;
        s->tail = (s->tail + 1) % s->length;
    }
    else
    {
        s->grow_count--;
        s->count++;
    }
    if(m->grid[new_y][new_x] == EGG)
    {
        m->eggs_count--;
        s->points++;
        s->grow_count+=3;
    }
    int current_head_x_position = s->body[s->head].x;
    int current_head_y_position = s->body[s->head].y;
    m->grid[current_head_y_position][current_head_x_position] = BODY;
    m->grid[new_y][new_x] = HEAD;
    s->head = (s->head + 1) % s->length;
    s->body[s->head].x = new_x;
    s->body[s->head].y = new_y;
}



void paint(struct map *m){
    for(int i =0;i<m->height;i++){
        for(int j =0;j<m->wide;j++){
            printf("%c", m->grid[i][j]);
        }
        printf("\n");
    }
}

void add_eggs(struct map *m, int voids){
    srand(time(NULL));

    m->eggs_count=voids;
    if (voids > 5){
        m->eggs_count=5;
        int rand_h, rand_w;
        for(int i =0; i<5;i++){
            do{
                rand_h = rand() % m->height;        
                rand_w = rand() % m->wide;
            }while(m->grid[rand_h][rand_w] != VOID);
            m->grid[rand_h][rand_w] = EGG;
        }
    } else{
        m->eggs_count=5;
        int break_for =0;
        for (int i = 0;i<m->height;i++){
            for (int j = 0;j<m->wide;j++){
                if (m->grid[i][j] == VOID){
                    m->grid[i][j] = EGG;
                    if (--voids == 0) {
                        break_for = 1;
                        break;
                    }
                }
            }
            if (break_for!=0)
                break;
        }
    }
}

void snake_body(struct snake s){
    int x, y;
    for (int i = s.tail; i!=s.head;i++){
        x = s.body[i].x;
        y = s.body[i].y;
        printf("%d,%d\n", x, y);
    }
    printf("%d,%d\n", s.body[s.head].x, s.body[s.head].y);
    printf("\n");
}