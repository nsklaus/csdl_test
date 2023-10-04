
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

// workaround circular includes,
// define structs first before loading makemap.h
typedef struct 
{
    int x, y; // Camera position
    int width, height; // Camera dimensions
    int speed; 
} Camera;

// wip
typedef struct 
{
    int width;
    int height;
} Map;

typedef struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
    bool action;
} Input;

typedef struct 
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    Map tilemap;
    Camera camera;
    Input input; 
    bool fullscreen;
    bool quitting;
} Game;

#include "makemap.h"
#include "player.h"


void load_map(const char* path);
void game_create(void);

Game* get_game(void);
//SDL_Texture*
SDL_Texture* texture;
SDL_Texture* largeTexture;

void game_run(void);
void game_destroy(void);

#endif // GAME_H

