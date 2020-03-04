#include "field.h"

void field_init (void) {
    for (int i = 0; i < FIELD_SIZE; i++)
        field[i] = TILE_EMPTY;
}

void field_set_tile (int x, int y, int type) {
    field[x + y * FIELD_WIDTH] = type;
}

int field_get_tile (int x, int y) {
    return field[x + y * FIELD_WIDTH];
}
