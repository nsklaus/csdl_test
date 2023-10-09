
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct 
{
    int x, y; // Camera position
    int width, height; // Camera dimensions
    int speed; 
} Camera;

typedef struct {
    char* type;     // doors, switches, pickup objects, elevators, floors, walls, ceillings ..
    int value;      // in case of doors: room number it links to.
    bool active;    // in case of switches, elevators and such
    bool solid;
    SDL_Rect rect;
} Tile_t;

typedef struct {
    int width;
    int height;
    int tilesize;
    int tileset_w;
    int tileset_h;
    SDL_Texture* texture[2];  // layers to render (foreground and background)
    Tile_t** collide;           // collision-layer
} Map_t;

typedef struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
    bool action;
} Input_t;

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
    bool can_move_up;
    bool can_move_down;
    bool can_move_left;
    bool can_move_right;

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
} Game_t;



extern void createLargeTexture(Game_t* game, const char* path);
void load_map(const char* path);
void game_create(void);
//SDL_Texture* largeTexture;

void game_run(void);
//void check_collision(SDL_Rect* a, SDL_Rect* b);
//void check_collision(Player_t *player, Map_t *map);

void render_game();
void game_destroy(void);

#endif // GAME_H

