
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
//#include "player.h"


// workaround circular includes,
// define structs first before loading makemap.h
typedef struct 
{
    int x, y; // Camera position
    int width, height; // Camera dimensions
    int speed; 
} Camera;

typedef struct {
    int width;
    int height;
    SDL_Texture* texture;  
} RenderLayer;

typedef struct {
    // shape data: rectangles and triangles for collision
} CollisionLayer;

typedef struct {
    int width;
    int height;
    int tilesize;
    int tileset_w;
    int tileset_h;
    RenderLayer R_Layer[3];  // Array of 3 render layers
    CollisionLayer C_layer;   // Single collision layer
} Map;

typedef struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
    bool action;
} Input;

typedef struct {
    int dx;
    int dy;
    int world_x;
    int world_y;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    int frameCount;
    float currentFrame;
    SDL_Texture* texture;
} Player;

typedef struct 
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    Map tilemap;
    Camera camera;
    Input input; 
    Player player;
    bool fullscreen;
    bool quitting;
} Game;

#include "makemap.h"


void load_map(const char* path);
void game_create(void);

Game* get_game(void);
//SDL_Texture*
SDL_Texture* texture;
SDL_Texture* largeTexture;

void game_run(void);
void render_game();
void game_destroy(void);

#endif // GAME_H

