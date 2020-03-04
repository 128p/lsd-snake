#include "fruit.h"

void fruit_init (void) {
    fruit_replace();
}

void fruit_replace (void) {
    int rand_x, rand_y;

    do {
        rand_x = rand() % FIELD_WIDTH;
        rand_y = rand() % FIELD_HEIGHT;
    } while (field_get_tile(rand_x, rand_y) != TILE_EMPTY);

    field_set_tile(fruit[0], fruit[1], TILE_EMPTY);
    
    fruit[0] = rand_x;
    fruit[1] = rand_y;
    
    field_set_tile(fruit[0], fruit[1], TILE_FRUIT);
}
