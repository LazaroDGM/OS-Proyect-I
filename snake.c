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
static Stack MovesStack;

void start(struct map *map, struct snake *snake, int height, int wide);                //Function Prototype
int move(struct snake *s, struct map *m);                                                               //Function Prototype
Stack BFS(Snake *s, Map *m);                                                                               //Function Prototype


void main(){
    
    int height, wide;
    int presicion;
    scanf("%d%d%d", &height, &wide, &presicion);
    presicion = ((presicion - 1) % 10) + 1;
    struct snake snake;
    struct map map;
    start(&map, &snake, height, wide);

    // do{
    //     if(map.eggs_count==0){
    //         add_eggs(&map, snake.length - snake.count);
    //     }
    //     system("clear");
    //     printf("Puntuación: %d\n", snake.points);
    //     paint(&map);
    //     usleep(200000);
    // }
    // while (snake.length-snake.count>0 &&
    //     move(&snake,&map));


    do
    {
        MovesStack = BFS(&snake, &map);
        int count = (MovesStack.count / presicion);
        for (; count > 0; count--)
        {
            Body CurrentDestinyMove = pop(&MovesStack);
            moveTo(&map, &snake, CurrentDestinyMove.x, CurrentDestinyMove.y);
        }
    } while (MovesStack.count > 1);
    

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

Stack BFS(Snake *s, Map *m)
{
    Stack result_stack;
    Queue BFS_Queue;
    // Node* headNode;
    Body snake_head_coordinates;

    snake_head_coordinates.x = s->body[s->head].x;
    snake_head_coordinates.y = s->body[s->head].y;

    int matrix_height = m->height;
    int matrix_wide = m->wide;

   unsigned int distances_matrix[matrix_height][matrix_wide];

    //Descomentar esto si hace falta inicializar la matriz en cada casilla a 0....
    // for (size_t i = 0; i < matrix_height; i++)
    // {
    //     for (size_t j = 0; j < matrix_wide; j++)
    //     {
    //         distances_matrix[i][j] = 0;
    //     }
    // }
    
    //Descomentar en caso de que no se inicialice la Cola de forma automatica...
    // headNode->body = snake_head_coordinates;
    // BFS_Queue.count++;
    // headNode->body = snake_head_coordinates;
    // BFS_Queue.top = headNode;
    enqueue(&BFS_Queue, snake_head_coordinates);
    int egg_found = 0;
    while(1)
    {
        Body current_body = dequeue(&BFS_Queue);
        int current_body_x = current_body.x;
        int current_body_y = current_body.y;
        int current_distance_value = distances_matrix[current_body_y][current_body_x];
        for (size_t dir = 0; dir < 4; dir++)
        {
            int current_directional_x = x_directional_offset[dir];
            int current_directional_y = y_directional_offset[dir];
            Body current_directional_corrdinates;
            current_directional_corrdinates.x = current_directional_x;
            current_directional_corrdinates.y  = current_directional_y;
            if(0 == IsAValidCoordinate(current_directional_corrdinates, matrix_wide, matrix_height) ||
                        m->grid[current_directional_y][current_directional_x] == BODY                              ||
                        m->grid[current_directional_y][current_directional_x] == HEAD)
                 continue;
            if(m->grid[current_directional_y][current_directional_x] == EGG)
            {
                distances_matrix[current_directional_y][current_directional_x] = current_distance_value + 1;
                push(&result_stack, current_directional_corrdinates);
                egg_found = 1;
                break;
            }
            
            if(distances_matrix[current_directional_y][current_directional_x] == 0)
            {
                distances_matrix[current_directional_y][current_directional_x] = current_distance_value + 1;
                enqueue(&BFS_Queue, current_directional_corrdinates);
            }
        }
        if(egg_found == 1)break;
        if(BFS_Queue.count == 0)
        {
            push(&result_stack, current_body);
            break;
        }
    }

    Body destinyCell = peek_s(&result_stack);
    unsigned int way_distance = distances_matrix[destinyCell.y][destinyCell.x];
    for (unsigned int current_distance = way_distance - 1; current_distance > 0; current_distance--)
    {
        for (size_t dir = 0; dir < 4; dir++)
        {
            int new_x = destinyCell.x + x_directional_offset[dir];
            int new_y = destinyCell.y + y_directional_offset[dir];
            if(distances_matrix[new_y][new_x] == current_distance)
            {
                destinyCell = NewBody(new_x, new_y);
                push(&result_stack, destinyCell);
                break;
            }
        }
        
    }
    return result_stack;
}

int IsAValidCoordinate(Body coordinate, int wide, int height)
{
    if(coordinate.x >= 0 && coordinate.x < wide && coordinate.y >= 0 && coordinate.y < height)return 1;
    return 0;
}