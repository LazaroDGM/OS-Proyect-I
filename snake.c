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
int lee(Map *m, Stack *s, int x, int y, int *frecuence);

void main(int argc, char *argv[]){
    
    int height, wide;
    height = wide = 0;

    height = (int)strtol(argv[1], NULL,0);
    wide = (int)strtol(argv[2], NULL,0);

    if (height < 5 || wide < 5){
        printf("Argumentos inválidos.\n Altura > 4 y Ancho > 4");
        return;
    }

    // Inicialización
    struct snake snake;
    struct map map;
    Stack road;
    new_stack(&road);

    start(&map, &snake, height, wide);
    add_eggs(&map, snake.length - snake.count);
    paint(&map);

    // El algoritmo implemntado busca caminos
    // de longitud mínima hacia algún huevo aleatorio alcanzable
    // En dicho caso la serpiente camina hast ese huevo.
    // En caso de no existir huevos alcanzables
    // se genera un camino lejano y solo se recorre 1/4 de dicho camino
    // para luego ejecutar de nuevo el algoritmo
    // y alterar el camino.

    // NOTA: Sabemos que este algoritmo no es el más óptimo ya que
    // una estrategia de zig-zag resulta más ganadora, sin embargo
    // esta vía nos permitía aplicar más conocimientos sobre nuestro
    // dominio con el lenguaje C

    // Indica hasta que punto del camino en la pila road
    // se moverá la serpiente.
    int frecuence = 0;
    Body next_move;
    while (snake.length-snake.count>0 &&
        lee(&map, &road, snake.body[snake.head].x , snake.body[snake.head].y, &frecuence)){
        
        do {
            usleep(200000);
            system("clear");
            next_move = pop(&road);
            moveTo(&map, &snake, next_move.x,next_move.y);
            printf("Puntuación: %d\n", snake.points);
            paint(&map);

            // Genera huevos cuando no hay en el tablero
            if(map.eggs_count==0){
                add_eggs(&map, snake.length - snake.count);
            }
            if(frecuence-- <= 0){
                while (road.count>0){
                    pop(&road);
                }
            }
        } while (road.count>0);
    }
    printf("Juego terminado");
}

// Método para inicializar el mapa y la serpiente
void start(struct map *m, struct snake *s, int height, int wide){
    
    // Espacio reservado para la matriz del mapa
    // Para mayor comodidad la matriz será de char
    // cumpliendo con lo establecido en la orden del proyecto
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

    // Se le asigna a la serpiente un tamaño igual al
    // del tablero ya que es el mayor espacio posible
    // que puede ocupar
    s->length = height*wide;
    struct body *bodys = calloc(height*wide, sizeof(struct body));

    // Se crea el cuerpo inicial
    for(int i = 3;i>0;i--){
        bodys[i-1].x = wide/2 + i -3;
        bodys[i-1].y = height/2;
    }
    s->body = bodys;
    
    // Se lleva un índice para reconocer el lugar de la cabeza
    s->head = 2;
    // y de la cola de la serpiente
    s->tail = 0;

    // Indica el tamaño real de la serpiente
    s->count = 3;
    // Indica los espacios que le falta por crecer
    s->grow_count = 0;
    // Indica la puntuación que tiene basada en la cantidad
    // de huevos comidos
    s->points=0;

    for(int i =0;i<s->count-1;i++){
        m->grid[s->body[s->tail+i].y][s->body[s->tail+i].x] = BODY;
    }
    m->grid[s->body[s->head].y][s->body[s->head].x]=HEAD;
}

// Algoritmo para generar un camino desde la serpiente
// hasta un huevo aleatorio alcanzable
// o hasta un camino sin huevos lejando
// del cual solo se recorre 1/4 del camino
int lee(Map *m, Stack *s, int x, int y, int *frecuence){
    Queue q;
    new_queue(&q);

    Body b;
    b.x = x;
    b.y = y;
    enqueue(&q, b);

    // Asignar espacio para la matriz
    int ** matrix=(int **)calloc(m->height,sizeof(int *));
    for (int i =0; i<m->height;i++){
        matrix[i]= (int *)calloc(m->wide, sizeof(int));
    }

    // Inicializar la matriz con:
    // -1: para espacios vacíos 
    // -2: para el cuerpo de la serpiente
    for (int i = 0; i<m->height;i++){
        for(int j =0;j<m->wide;j++){
            if (m->grid[i][j] == BODY ||
                m->grid[i][j] == HEAD){
                    matrix[i][j]= -2;
                }
            else
                matrix[i][j]=-1;
        }
    }

    // Pila para colocar huevos alcanzables
    Stack eggs;
    new_stack(&eggs);

    matrix[y][x]=0;
    int len = 1;
    int egg_x = -1 , egg_y = -1;
    int max_x = -1 , max_y = -1;    

    // Inicio del algoritmo de Lee
    // que es una versión del algoritmo BFS
    while (q.count>0) {
        b = dequeue(&q);
        int new_x, new_y;
        for (int dir = 0; dir < 4; dir++){
            
            new_x = b.x + x_directional_offset[dir];
            new_y = b.y + y_directional_offset[dir];
            if(new_x>=0 && new_y >=0 &&
                new_x<m->wide && new_y<m->height && 
                matrix[new_y][new_x] == -1){
                
                max_x =new_x;
                max_y =new_y;
                matrix[max_y][max_x] = matrix[b.y][b.x] + 1;

                Body new;
                new.x = max_x;
                new.y = max_y;
                enqueue(&q,new);
                if (m->grid[new_y][new_x]==EGG){
                    Body egg;
                    egg.x = new_x;
                    egg.y = new_y;
                    push(&eggs, egg);
                }
            }
        }
    }

    if(max_x == -1){
        return 0;
    }

    if (eggs.count>0){
        srand(time(NULL));
        int r = rand() % (eggs.count);
        while (eggs.count>0){               
            if (eggs.count==r+1){
                push(s,peek_s(&eggs));
            }
            pop(&eggs);
        }
    }else{
        b.x = max_x;
        b.y = max_y;
        push(s,b);
    }
    
    if(m->grid[peek_s(s).y][peek_s(s).x]==EGG){
        *frecuence = matrix[peek_s(s).y][peek_s(s).x];
    } else{
        // El camino si huevos actualiza la frecuencia
        // con que se hará el próximo BFS
        *frecuence = matrix[peek_s(s).y][peek_s(s).x]/4;
    }

    // Generación del camino por el cual se moverá
    // la serpiente    
    for (int i = matrix[peek_s(s).y][peek_s(s).x]-1;i>0;i--){
        int new_x, new_y;
        for (int dir = 0; dir < 4; dir++){            
            new_x = peek_s(s).x + x_directional_offset[dir];
            new_y = peek_s(s).y + y_directional_offset[dir];
            if(new_x>=0 && new_y >=0 &&
                new_x<m->wide && new_y<m->height && 
                matrix[new_y][new_x] == matrix[peek_s(s).y][peek_s(s).x]-1){
                b.x = new_x;
                b.y = new_y;
                push(s, b);
                break;
            }
        }
    }
    return 1;
}

// Método para mover de forma random
// a la serpiente a lugares válidos
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

                directionanding[directionanding_index] = new_posible_way;
                directionanding_index++;
            }
    }
    if(directionanding_index == 0) return 0;
    // Generar una posición aleatoria de las válidas
    srand(time(NULL));
    int r = rand() % (directionanding_index);
    
    if(m->grid[directionanding[r].y][directionanding[r].x] == EGG) {
        m->eggs_count--;
        s->points++;
        s->grow_count+=3;
    }
    
    moveTo(m, s, directionanding[r].x, directionanding[r].y);

    return 1;
}