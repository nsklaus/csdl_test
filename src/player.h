#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <stdbool.h>
#include "game.h"



Player player_init(Game* game);
void player_update(Game* game, int frameTime);
void player_render(Game* game);
void player_change_animation(int frameCount, int yPosition, Game* game);
void player_destroy(Game* game);

#endif // PLAYER_H