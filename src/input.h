
#ifndef INPUT_H
#define INPUT_H


#include <stdio.h>
#include "game.h"

void input_handle_events(Game_t* game);
void toggle_fullscreen(Game_t* game);
bool move_player_if_possible(Game_t* game, int dx, int dy);
#endif // INPUT_H
