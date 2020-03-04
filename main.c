#include "main.h"

unsigned int *buffer;

unsigned int *neighbor (int cx, int cy, int xoff, int yoff) {
    int xx = cx + xoff;
    int yy = cy + yoff;

    if (xx >= SCREEN_WIDTH) xx = SCREEN_WIDTH-1;
    if (xx < 0) xx = 0;
    if (yy >= SCREEN_HEIGHT) yy = SCREEN_HEIGHT-1;
    if (yy < 0) yy = 0;
    
    return (buffer + xx + yy * SCREEN_WIDTH);
}

int main (int argc, char **argv) {
    SDL_Window *window;
    static SDL_Surface *screen;
    bool lsd_mode = true;
    bool paused = false;
    int gameTime = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(0, "SDL_Init: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
        );

    if (window == NULL) {
        SDL_LogError(0, "SDL_CreteWindow: %s", SDL_GetError());
        return EXIT_FAILURE;        
    }

    screen = SDL_GetWindowSurface(window);
    buffer = (unsigned int *)screen->pixels;

    field_init();

    /* for (int y = 5; y < FIELD_HEIGHT-5; y++) { */
    /*     for (int x = 5; x < FIELD_WIDTH-5; x++) { */
    /*         if (y == 5 || y == FIELD_HEIGHT-5 && (x == 5 || x == FIELD_WIDTH-5)) */
    /*             field_set_tile(x, y, TILE_SNAKE); */
    /*     } */
    /* } */
    
    snake_init();
    fruit_init();

    snake_head[0] = snake_head[1] = 0;
    snake_body_push(snake_head[0], snake_head[1]);
          
    bool quit = false;
    SDL_Event event;
    float previousTime = SDL_GetTicks();
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT ||
               event.type == SDL_WINDOWEVENT_CLOSE)
            {
                quit = true;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                int key = event.key.keysym.sym;
                if (key == SDLK_ESCAPE || key == SDLK_q) {
                    quit = true;
                    break;
                }

                if (key == SDLK_l) lsd_mode=!lsd_mode;
                if (key == SDLK_p) paused=!paused;

                if (!paused) {
                    if (key == SDLK_w) snake_set_dir(SNAKE_DIR_UP);
                    if (key == SDLK_s) snake_set_dir(SNAKE_DIR_DOWN);
                    if (key == SDLK_a) snake_set_dir(SNAKE_DIR_LEFT);
                    if (key == SDLK_d) snake_set_dir(SNAKE_DIR_RIGHT);
                }
            }
        }

        if (!paused) {
            float currentTime = SDL_GetTicks();
            if (currentTime > previousTime + GAME_TICK_SPEED) {
                snake_update();
                gameTime++;
                previousTime = currentTime;
            }
        }

        SDL_FillRect(screen, NULL, COLOR_BACKGROUND);
        
        SDL_Rect brush_rect = { 0, 0, TILE_WIDTH-1, TILE_HEIGHT-1 };
        SDL_Rect brush_shadow_rect = { 0, 0, TILE_WIDTH-1, (TILE_HEIGHT/2)-1 };
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            for (int x = 0; x < FIELD_WIDTH; x++) {
                brush_rect.x = x * TILE_WIDTH;
                brush_rect.y = y * TILE_HEIGHT;

                brush_shadow_rect.x = brush_rect.x;
                brush_shadow_rect.y = brush_rect.y + TILE_HEIGHT;

                switch (field_get_tile(x, y)) {
                    case TILE_SNAKE:
                        SDL_FillRect(screen, &brush_rect, COLOR_SNAKE);
                        SDL_FillRect(screen, &brush_shadow_rect, darken_hex(COLOR_SNAKE, 5));
                        break;

                    case TILE_FRUIT:
                        SDL_FillRect(screen, &brush_shadow_rect, darken_hex(COLOR_SNAKE, 9));
                        SDL_FillRect(screen, &brush_rect, COLOR_FRUIT);
                        break;

                    default:
                        break;
                }
            }
        }

        if (!paused) {
            if (lsd_mode) {
                int range = TILE_WIDTH / 2;
                /* Ignore this, it was my cat */
                if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
                for (int y = 0; y < SCREEN_HEIGHT; y++) {
                    for (int x = 0; x < SCREEN_WIDTH; x++) {
                        unsigned int *rgb = (buffer + x + y * SCREEN_WIDTH);

                        if (*rgb == 0x000000) {
                            if (y%(SDL_GetTicks()%9 ? 5 : 9)==0)
                                *rgb |= ((0x550a00) ^ y);
                            continue;
                        }

                        int r1 = range;
                        int r2 = range / 2;
                        int r3 = range / 3;
                        int r4 = range / 4;

                        /* int rm = (*rgb >> 16) & 255; // b */
                        /* int gm = (*rgb >> 8) & 255; */
                        /* int bm = (*rgb & 255); */
                    
                        /* *neighbor(x, y, -r4, -r4) |= ((*rgb >> 8) & 255) * 4; */
                        /* *neighbor(x, y, r4, r4) |= (*rgb << 8) * 4; */

                        int t = SDL_GetTicks();
                        *neighbor(x, y, -r4, -r4) |= ((*rgb >> 4) & 255) * 2;
                        *neighbor(x, y, r4, r4) |= (*rgb << 8) * (t % 4);
                        *neighbor(x, y, +2, -1) |= ((*rgb >> 8) & 255);
                    }
                }
                if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
            }


            SDL_UpdateWindowSurface(window);
        }

    }

    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}


        /* if (lsd_mode) { */
        /*     /\* Ignore this, it was my cat *\/ */
        /*     if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen); */
        /*     for (int y = 3; y < SCREEN_HEIGHT-3; y++) { */
        /*         for (int x = 3; x < SCREEN_WIDTH-3; x++) { */
        /*             if (*(buffer + x + y * SCREEN_WIDTH) == 0) */
        /*                 continue; */
                    
        /*             *(buffer + (x+2) + y * SCREEN_WIDTH) |= */
        /*                 ((*(buffer + (x+1) + y * SCREEN_WIDTH)<<16) * 2); */
                
        /*             *(buffer + (x+3) + y * SCREEN_WIDTH) |= */
        /*                 ((*(buffer + (x+2) + y * SCREEN_WIDTH)<<16) * 2); */

        /*             *(buffer + (x-2) + y * SCREEN_WIDTH) |= */
        /*                 ((*(buffer + (x-1) + y * SCREEN_WIDTH)>>8&16) * 2); */
                
        /*             *(buffer + (x-3) + y * SCREEN_WIDTH) |= */
        /*                 ((*(buffer + (x-1) + y * SCREEN_WIDTH)>>8&0xff) * (((int)previousTime)%10)); */

        /*             *(buffer + x + (y+1) * SCREEN_WIDTH) |= */
        /*                 (*(buffer + (x-1) + y * SCREEN_WIDTH)>>7&0xff) * ((SDL_GetTicks()%2)); */

        /*             *(buffer + x + (y-3) * SCREEN_WIDTH) |= */
        /*                 (*(buffer + (x-2) + (y-2) * SCREEN_WIDTH)>>8&0xff) * 2; */

        /*         } */
        /*     } */
        /*     if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen); */
        /* } */


