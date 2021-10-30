#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snklib.h"

// Método para mover la serpiente una sola casilla
void moveTo(struct map *m, struct snake *s, int new_x, int new_y)
{
    // El movimiento se simula cambiando los índices de la cabeza
    // y la cola. Cuando crece solo se modifica la cabeza
    // para mayor comodidad y eficiencia el array en que se
    // guarda el cuerpo de la serpiente se cnsidera circular

    // Caso en que NO tiene que crecer
    if(s->grow_count == 0) {
        m->grid[s->body[s->tail].y][s->body[s->tail].x] = VOID;
        s->tail = (s->tail + 1) % s->length;
    } else {
        // Caso en que SÍ tiene que crecer
        s->grow_count--;
        s->count++;
    }

    // Si se mueve hacia un huevo se actualizan
    // la puntuación y los espacios por crecer
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


// Para pintar el mapa
void paint(struct map *m){
    for(int i =0;i<m->height;i++){
        for(int j =0;j<m->wide;j++){
            printf("%c", m->grid[i][j]);
        }
        printf("\n");
    }
}

// Genera los huevos aleatorios
void add_eggs(struct map *m, int voids){

    srand(time(NULL));
    m->eggs_count=voids;
    // Si el espacio es disponible es mayor que 5
    // se generan 5 huevos aleatorios
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
        // Si el espacio disponible es 5 o menor
        // se generan direcatmente esa cantidad de huevos
        // en cada espacio vacío.
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

// Usada solo para saber cuál es el cuerpo de la serpiente
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