#ifndef SNAKE_H
#define SNAKE_H

#include "defs.h"
#include "field.h"
#include "fruit.h"

int snake_body_x[(FIELD_WIDTH-1)*TILE_WIDTH];
int snake_body_y[(FIELD_HEIGHT-1)*TILE_HEIGHT];
int snake_head[2];

int snake_dir;
int snake_len;
int snake_max_len;

void snake_body_push (int x, int y);
void snake_body_pop (void);
void snake_update (void);
void snake_set_dir (int dir);
void snake_init (void);

#endif /* SNAKE_H */
