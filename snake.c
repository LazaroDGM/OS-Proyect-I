#define EGG 'x'
#define BODY 'o'
#define HEAD '@'
#define VOID '.'

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int points;
};

typedef struct map{
    char** grid;
    int height;
    int wide;
    int eggs_count;
};


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