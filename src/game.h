
#ifndef GAME_H
#define GAME_H

//#include "makemap.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct 
{
    int x, y; // Camera position
    int width, height; // Camera dimensions
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    //int speed; 
} Camera;

typedef struct {
    char* type;     // doors, switches, pickup objects, elevators, floors, walls, ceillings ..
    int value;      // in case of doors: room number it links to.
    bool active;    // in case of switches, elevators and such
    bool solid;     // for collision
    SDL_Rect rect;
} Tile_t;

typedef struct {
    int width;
    int height;
    int tilesize;
    int tileset_w;
    int tileset_h;
    SDL_Texture* texture[2];  // layers to render (foreground and background)
    Tile_t** tile;            // collision-layer
} Map_t;

typedef struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
    bool action;
    bool jump;
} Input_t;

typedef struct {
    int dx;                 // directional velocity    
    int dy;
    float vy;               // Vertical velocity
    int world_x;
    int world_y;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    SDL_Rect feetRect;      // test if onGround
    int frameCount;
    float currentFrame;
    SDL_Texture* texture;
    bool isGrounded;        // gravity and jump
    bool up;
    bool down;
    bool left;
    bool right;
    bool blocked;           // cannot move (collision)

} Player_t;

typedef struct 
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    Map_t map;
    Camera camera;
    Input_t input; 
    Player_t player;
    bool fullscreen;
    bool quitting;
    bool debug;
} Game_t;



extern void map_create(Game_t* game, const char* path);
extern void map_update(Game_t* game);
extern void map_render(Game_t* game);
void map_load(const char* path);
void game_create(void);
void game_loop(void);
void game_render();
void game_destroy(void);

#endif // GAME_H

