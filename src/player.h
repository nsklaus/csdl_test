#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <stdbool.h>
#include "game.h"

typedef enum 
{
    TILESIZE = 48,
    RUNNING_L = 0,      // first row
    RUNNING_R = 48,     // second row
    STANDING_L = 96,    // third ..
    STANDING_R = 144,
    FALLING_L = 192,
    FALLING_R = 240,
    STANDING_F = 288,   // alternate standing, facing the screen
    JUMPING_L = 432,
    JUMPING_R = 480,
    RUN_GUN_L = 528,
    RUN_GUN_R = 576,
    
} AnimationType;

Player player_init(Game* game);
void player_update(Game* game, float deltaTime);
void player_render(Game* game);
void player_change_animation(int frameCount, AnimationType animType, Game* game);
void player_destroy(Game* game);

#endif // PLAYER_H