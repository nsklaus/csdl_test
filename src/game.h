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



typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running;
} Game;

Game* game_create(void);
//SDL_Texture* load_map(const char* path);
void game_run(Game* game);
void game_destroy(Game* game);

#endif // GAME_H

