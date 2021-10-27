#define EGG 'x'
#define BODY 'o'
#define HEAD '@'
#define VOID '.'

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



enum direction{ UP, RIGHT, DOWN, LEFT };

typedef struct body{
    int x, y;
};

typedef struct snake{
    struct body *body;
    int head;
    int tail;
    int grow_count;
    int length;
    int count;
    enum direction dir;
    int points;
};

typedef struct map{
    char** grid;
    int height;
    int wide;
    int eggs_count;
};


static int x_directional_offset[] = {-1, 0, 1, 0 };
static int y_directional_offset[] = {0, 1, 0, -1 };
static struct body directionanding[4];
static int directionanding_index = 0;

int Move(struct snake *s, struct map *m);                                                                                                      // Function Prototype
void MoveTo(struct map *m, struct snake *s, int new_x, int new_y);                                                         // Function Prototype
void start(struct map *map, struct snake *snake, int height, int wide);
void paint(struct map *map);
void len(int **arr);

void main(){

    int height, wide;

    scanf("%d%d", &height, &wide);


    struct snake snake;
    struct map map;

    start(&map, &snake, height, wide);

    add_eggs(&map, snake.length - snake.count);

    paint(&map);
    system("Pause");
}



int Move(struct snake *s, struct map *m)
{
    int head_x = s->body[s->head].x;
    int head_y = s->body[s->head].y;
    int tail_x = s->body[s->tail].x;
    int tail_y = s->body[s->tail].y;

    for (unsigned int  direc = 0; direc < 4; direc++)
    {
        if(s->dir == (direc + 2) % 4) continue;
        int new_x = head_x + x_directional_offset[direc];
        int new_y = head_y + y_directional_offset[direc];
        if(new_x >= 0 && new_x < m->wide &&                                                                                                       // Fuera de Rango de la Matriz
            new_y >= 0 && new_y < m->height &&                                                                                                    // Fuera de Rango de la Matriz
            (m->grid[new_x][new_y] != BODY       ||        (new_x == tail_x && new_y == tail_y && s->grow == 0)))            // No hay cuerpo de la serpiente en esa direccion, y su lo hay, es la cola y no se esta creciendo
            {   
                struct body new_posible_way;                                                                                                            // Inicializando 
                new_posible_way.x = new_x;                                                                                                          // Inicializando 
                new_posible_way.y = new_y;                                                                                                          // Inicializando 


                directionanding[directionanding_index] = new_posible_way;
                directionanding_index++;
            }
    }
    if(directionanding_index == 0) return 0;
    srand(time(NULL));
    int r = rand() % (directionanding_index + 1);
    
    MoveTo(m, s, directionanding[r].x, directionanding[r].y);
    return 1;
}

void MoveTo(struct map *m, struct snake *s, int new_x, int new_y)
{
    if(s->grow == 0) 
    {
        m->grid[s->body[s->tail].x][s->body[s->tail].y] = VOID;
        s->tail = (s->tail + 1) % s->length;
    }
    else
    {
        s->grow--;
        s->count++;
    }
    int current_head_x_position = s->body[s->head].x;
    int current_head_y_position = s->body[s->head].y;
    m->grid[current_head_x_position][current_head_y_position] = BODY;
    m->grid[new_x][new_y] = HEAD;
    s->head = (s->head + 1) % s->length;
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

    s->length = height*wide;
    struct body bodys[(*s).length];
    s->body = bodys;

    for(int i = 3;i>0;i--){
        bodys[i-1].x = wide/2 + i -3;
        bodys[i-1].y = height/2;
    }
    s->head = 2;
    s->tail = 0;
    s->count = 3;
    s->grow_count = 0;

    for(int i =0;i<s->count-1;i++){
        m->grid[s->body[s->tail+i].y][s->body[s->tail+i].x] = BODY;
    }
    m->grid[s->body[s->head].y][s->body[s->head].x]=HEAD;
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