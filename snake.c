#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snklib.h"
#include "utillib.h"


static int x_directional_offset[] = {-1, 0, 1, 0 };
static int y_directional_offset[] = {0, 1, 0, -1 };
static struct body directionanding[4];
static int directionanding_index = 0;

void start(struct map *map, struct snake *snake, int height, int wide);
int move(struct snake *s, struct map *m);  

void main(){
    
    int height, wide;

    scanf("%d%d", &height, &wide);

    struct snake snake;
    struct map map;

    start(&map, &snake, height, wide);

    do{
        if(map.eggs_count==0){
            add_eggs(&map, snake.length - snake.count);
        }
        system("clear");
        printf("Puntuación: %d\n", snake.points);
        paint(&map);
        usleep(200000);
    }
    while (snake.length-snake.count>0 &&
        move(&snake,&map));


    //snake_body(snake);
}

void start(struct map *m, struct snake *s, int height, int wide){

    char ** grid=(char **)calloc(height,sizeof(char *));
    for (int i =0; i<height;i++){
        grid[i]= (char *)calloc(wide, sizeof(char));
    }

    for(int i =0;i<height;i++){
        for(int j =0;j<wide;j++){
            grid[i][j] = VOID;
        }
    }
    m->grid = grid;
    m->height = height;
    m->wide = wide;
    m->eggs_count=0;

    s->length = height*wide;
    struct body *bodys = calloc(height*wide, sizeof(struct body));

    for(int i = 3;i>0;i--){
        bodys[i-1].x = wide/2 + i -3;
        bodys[i-1].y = height/2;
    }
    s->body = bodys;
    
    s->head = 2;
    s->tail = 0;
    s->count = 3;
    s->grow_count = 0;
    s->points=0;

    for(int i =0;i<s->count-1;i++){
        m->grid[s->body[s->tail+i].y][s->body[s->tail+i].x] = BODY;
    }
    m->grid[s->body[s->head].y][s->body[s->head].x]=HEAD;
}

int move(struct snake *s, struct map *m){
    int head_x = s->body[s->head].x;
    int head_y = s->body[s->head].y;
    int tail_x = s->body[s->tail].x;
    int tail_y = s->body[s->tail].y;

    int new_x;
    int new_y;
    directionanding_index=0;
    for (int  direc = 0; direc < 4; direc++){
        new_x = head_x + x_directional_offset[direc];
        new_y = head_y + y_directional_offset[direc];

            // Fuera de Rango de la Matriz
        if(new_x >= 0 && new_x < m->wide && 
            new_y >= 0 && new_y < m->height &&
            // No hay cuerpo de la serpiente en esa direccion,
            (m->grid[new_y][new_x] != BODY || 
            // O si es la cola y no se esta creciendo
            (new_x == tail_x &&
            new_y == tail_y &&
            s->grow_count == 0)))
            {   
                // Inicializando
                struct body new_posible_way;
                new_posible_way.x = new_x;
                new_posible_way.y = new_y;
                
                //printf("P: (%d,%d)",new_x,new_y);

                directionanding[directionanding_index] = new_posible_way;
                directionanding_index++;
            }
    }
    //printf("\n");
    if(directionanding_index == 0) return 0;
    srand(time(NULL));
    int r = rand() % (directionanding_index);
    
    if(m->grid[directionanding[r].y][directionanding[r].x] == EGG)
    {
        m->eggs_count--;
        s->points++;
        s->grow_count+=3;
    }
    //printf("r:%d (%d,%d)\n",r,directionanding[r].x,directionanding[r].y);
    moveTo(m, s, directionanding[r].x, directionanding[r].y);

    return 1;
}

