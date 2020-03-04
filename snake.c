#include "snake.h"

void snake_init (void) {
    snake_dir = SNAKE_DIR_RIGHT; // 1
    snake_len = 0;
    snake_max_len = SNAKE_INIT_LENGTH;
}

void snake_body_push (int x, int y) {
    field_set_tile(x, y, TILE_SNAKE);

    snake_body_x[snake_len] = x;
    snake_body_y[snake_len] = y;

    snake_len++;
}

void snake_body_pop (void) {
    field_set_tile(snake_body_x[0], snake_body_y[0], TILE_EMPTY);

    for (int i = 0; i < snake_len; i++) {
        snake_body_x[i] = snake_body_x[i+1];
        snake_body_y[i] = snake_body_y[i+1];
    }
    
    snake_len--;
}

void snake_update (void) {
    if (snake_dir == SNAKE_DIR_UP)
        snake_head[1] -= 1;

    if (snake_dir == SNAKE_DIR_DOWN)
        snake_head[1] += 1;

    if (snake_dir == SNAKE_DIR_LEFT)
        snake_head[0] -= 1;

    if (snake_dir == SNAKE_DIR_RIGHT)
        snake_head[0] += 1;

    if (snake_head[0] >= FIELD_WIDTH)  snake_head[0] = 0;
    if (snake_head[1] >= FIELD_HEIGHT) snake_head[1] = 0;
    if (snake_head[0] < 0) snake_head[0] = FIELD_WIDTH-1;
    if (snake_head[1] < 0) snake_head[1] = FIELD_HEIGHT-1;

    switch (field_get_tile(snake_head[0], snake_head[1])) {
        case TILE_FRUIT:
            SDL_Delay(30);
            if (snake_max_len >= FIELD_SIZE) {
                printf("You won the game!\nWithdraw your cookie in the nearest bank!");
                SDL_Delay(3000);
                exit(EXIT_SUCCESS);
            } else {
                fruit_replace();
                snake_max_len++;
            }
            break;
            

        case TILE_SNAKE:
            for (int i = 0; i < 10; i++)
                printf("*****************\n");
            
            printf("You lose!\n");
            
            for (int i = 0; i < 10; i++)
                printf("*****************\n");
            
            SDL_Delay(2000);
            exit(EXIT_SUCCESS);
            break;

        default:
            break;
    }

    snake_body_push(snake_head[0], snake_head[1]);

    if (snake_len >= snake_max_len)
        snake_body_pop();
}

void snake_set_dir (int dir) {
    if (-snake_dir != dir) snake_dir = dir;
}
