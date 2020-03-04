#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#define GAME_TICK_SPEED 115

#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 256

#define TILE_WIDTH  16
#define TILE_HEIGHT 16

#define FIELD_WIDTH  (SCREEN_WIDTH / TILE_WIDTH)
#define FIELD_HEIGHT (SCREEN_HEIGHT / TILE_HEIGHT)

#define FIELD_SIZE (FIELD_WIDTH * FIELD_HEIGHT)

#define SNAKE_INIT_LENGTH 4

#define SNAKE_DIR_UP     1
#define SNAKE_DIR_DOWN  -1
#define SNAKE_DIR_RIGHT  2
#define SNAKE_DIR_LEFT  -2

#define TILE_EMPTY 0
#define TILE_SNAKE 1
#define TILE_FRUIT 2

#define COLOR_BACKGROUND 0x00000000
#define COLOR_SNAKE      0xff00ff00
#define COLOR_FRUIT      0xffff55ff

#endif /* DEFS_H */
