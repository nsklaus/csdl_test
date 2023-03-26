//
//  game.h
//  mygame
//
//  Created by klaus on 24/03/2023.
//

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
//#include "makemap.h"
#include "graphics.h"


void load_map(const char* path);

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running;
} Game;


void game_create(void);

Game* get_game(void);
//SDL_Texture*

void game_run(void);
void game_destroy(void);

#endif // GAME_H

