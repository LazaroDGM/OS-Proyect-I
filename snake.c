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
    int grow;
    int length;
    int count;
};

typedef struct map{
    char** grid;
    int height;
    int wide;
};



void inicio(struct map *map, struct snake *snake, int height, int wide);
void pintar(struct map *map);
void len(int **arr);


void main(){

    int height, wide;

    scanf("%d%d", &height, &wide);


    struct snake snake;
    struct map map;

    int t[20][10] = {0};
    printf("%d\n", t[4][5]);

    inicio(&map, &snake, height, wide);

    printf("%d\n", snake.count);

    //char map[height][wide];

    //printf("%d", sizeof(map));
}

void len(int **arr){
    
    arr[2][4] = 123;
}

void inicio(struct map *map, struct snake *snake, int height, int wide){
    char grid[height][wide];
    for(int i =0;i<height;i++){
        for(int j =0;j<wide;j++){
            grid[i][j] = VOID;
        }
    }
    struct map m=*map;
    m.grid = grid;
    m.height = height;
    m.wide = wide;


    struct snake* snk = snake;
    (*snake).length = height*wide;
    struct body bodys[(*snake).length];
    (*snake).body = bodys;
    (*snake).head = &((*snake).body);
    (*snake).tail = &((*snake).body);
    (*snk).count = 1;
    (*snake).grow = 0;
}

//void mover(char *map, struct snake *snake);

void pintar(struct map *map){
    return;
    //struct map m = *map;
    //char g[][]= m.grid
    //for(int i =0;i<m.height;i++){
    //    for(int j =0;j<m.wide;j++){
    //        printf("%c", *(map+i*wide+j));
    //    }
    //    printf("\n");
    //}
}