#define EGG 'x'
#define BODY 'o'
#define HEAD '@'
#define VOID '.'

#include <stdio.h>

typedef struct body{
    int x, y;
};

typedef struct snake{
    struct body *body;
    struct body *head;
    struct body *tail;
    int grow_count;
    int length;
    int count;
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

    paint(&map);
    //char map[height][wide];

    //printf("%d", sizeof(map));
}

void len(int **arr){
    
    arr[2][4] = 123;
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
    s->head = s->body+2;
    s->tail = s->body;
    s->count = 3;
    s->grow_count = 0;

    for(int i =0;i<s->count-1;i++){
        m->grid[s->tail[i].y][s->tail[i].x] = BODY;
    }
    m->grid[s->head->y][s->head->y]=HEAD;
}

void paint(struct map *m){
    
    for(int i =0;i<m->height;i++){
        for(int j =0;j<m->wide;j++){
            printf("%c", m->grid[i][j]);
        }
        printf("\n");
    }
}