
#ifndef INPUT_H
#define INPUT_H


#include <stdio.h>
#include "game.h"

typedef struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
    //bool quit_requested;
    // possibly other input states
} Input;

void input_handle_events(Game* game);
void toggle_fullscreen(Game* game);

#endif // INPUT_H
