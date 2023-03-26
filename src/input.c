//
//  input.c
//  mygame
//
//  Created by klaus on 24/03/2023.
//

#include "input.h"

void input_handle_events(Game* game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->is_running = false;
                break;
            case SDL_KEYDOWN:
                // Handle keydown event
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Handle mouse button down event
                break;
            default:
                break;
        }
    }
}
