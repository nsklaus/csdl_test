
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "makemap.h"
#include "graphics.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running;
} Game;

void load_map(const char* path);
void game_create(void);

Game* get_game(void);
//SDL_Texture*
SDL_Texture* texture;
SDL_Texture* largeTexture;

void game_run(void);
void game_destroy(void);

#endif // GAME_H

