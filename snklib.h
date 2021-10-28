#define EGG 'x'
#define BODY 'o'
#define HEAD '@'
#define VOID '.'

enum direction{ LEFT=0, UP, RIGHT, DOWN};

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
void paint(struct map *map);
void snake_body(struct snake s);