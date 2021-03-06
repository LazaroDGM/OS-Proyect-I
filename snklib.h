#define EGG 'x'
#define BODY 'o'
#define HEAD '@'
#define VOID '.'

enum direction{ LEFT=0, UP, RIGHT, DOWN};

// Tupla que contiene coordenadas x y y
// Su nombre es body porque fundamentalmente
// se usan para el cuerpo de la serpiente.
typedef struct body{
    int x, y;
}Body;

typedef struct snake{
    struct body *body;
    int head;
    int tail;
    int grow_count;
    int length;
    int count;
    int points;
}Snake;

typedef struct map{
    char** grid;
    int height;
    int wide;
    int eggs_count;
}Map;

void moveTo(struct map *m, struct snake *s, int new_x, int new_y);
void add_eggs(struct map *m, int voids);
void paint(struct map *map);
void snake_body(struct snake s);