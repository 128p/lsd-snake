#ifndef FIELD_H
#define FIELD_H

#include "defs.h"

int field[FIELD_SIZE];

void field_init (void);
void field_set_tile (int x, int y, int type);
int field_get_tile (int x, int y);

#endif /* FIELD_H */
