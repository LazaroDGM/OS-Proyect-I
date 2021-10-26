#define EGG 'x'
#define BODY 'o'
#define HEAD '@'
#define VOID '.'

#include <stdio.h>
#include<stdlib.h>
#include<time.h>

enum direction{ UP, RIGHT, DOWN, LEFT };
typedef struct body{
    int x, y;
};

typedef struct snake{
    struct body *body;
    struct body *head;
    struct body *tail;
    int grow;
    int length;
    int count;
    enum direction dir;
};

typedef struct map{
    char** grid;
    int height;
    int wide;
};

static int x_directional_offset[] = {-1, 0, 1, 0 };
static int y_directional_offset[] = {0, 1, 0, -1 };
static struct body directionanding[4];
static int directionanding_index = 0;
int Move(struct snake s, struct map m);                                                                                                      // Function Prototype
void MoveTo(struct map m, struct snake s, int x_offset, int y_offset);                                                         // Function Prototype


int Move(struct snake s, struct map m)
{
    int head_x = s.head->x;
    int head_y = s.head->y;
    char **grid = m.grid;

    for (unsigned int  direc = 0; direc < 4; direc++)
    {
        int new_x = head_x + x_directional_offset[direc];
        int new_y = head_y + y_directional_offset[direc];
        if(new_x > 0 && new_x < m.wide &&                                                                                                       // Fuera de Rango de la Matriz
            new_y > 0 && new_y < m.height &&                                                                                                    // Fuera de Rango de la Matriz
            (m.grid[new_x][new_y] != BODY       ||        (new_x == s.tail->x && new_y == s.tail->y && s.grow == 0)))            // No hay cuerpo de la serpiente en esa direccion, y su lo hay, es la cola y no se esta creciendo
            {   
                struct body new_posible_way;                                                                                                            // Inicializando 
                new_posible_way.x = new_x;                                                                                                          // Inicializando 
                new_posible_way.y = new_y;                                                                                                          // Inicializando 


                directionanding[directionanding_index] = new_posible_way;
                directionanding_index++;
            }
    }
    srand(time(NULL));
    int r = rand() % (directionanding_index + 1);
    
    switch (r)
    {
    case UP:
            MoveTo(m, s, x_directional_offset[UP], y_directional_offset[UP]);

        break;
    case RIGHT:

        break;
    case DOWN:
        break;
    case LEFT:
        break;
    default:
        break;
    }
    
}
void MoveTo(struct map m, struct snake s, int x_offset, int y_offset)
{
    if(s.grow == 0) 
    {
        m.grid[s.tail->x][s.tail->y] = VOID;
        s.tail = 
    }
    else
    {

        s.tail->x = 
    }
    int current_head_x_position = s.head->x;
    int current_head_y_position = s.head->y;
    m.grid[current_head_x_position][current_head_y_position] = BODY;
    m.grid[current_head_x_position + x_offset][current_head_y_position + y_offset] = HEAD;
}

void main()
{
    printf("%d", UP);
}