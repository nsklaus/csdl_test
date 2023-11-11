#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "game.h"
#include "input.h"

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

void player_init(Game_t* game);
void player_update(Game_t* game, float deltaTime);
void move(Game_t* game, float deltaTime);
void grounded(Game_t* game);
void apply_gravity(Game_t* game);
void player_render(Game_t* game);
void player_animation(int frameCount, AnimationType animType, Game_t* game);
void player_destroy(Game_t* game);

#endif // PLAYER_H
