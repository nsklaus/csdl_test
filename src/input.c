#include "input.h"
#include <stdio.h>
#include "player.h"

void toggle_fullscreen(Game_t* game) {  // Added this function
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool isFullscreen = SDL_GetWindowFlags(game->window) & fullscreenFlag;

    SDL_SetWindowFullscreen(game->window, isFullscreen ? 0 : fullscreenFlag);
    SDL_ShowCursor(isFullscreen);
}

void input_handle_events(Game_t* game) 
{  
    SDL_Event event;
    
    // Resetting the input state
    game->input.up = false;
    game->input.down = false;
    game->input.left = false;
    game->input.right = false;
    game->quitting = false;
    game->fullscreen = false; 

    // Polling for events in the queue
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
            case SDL_QUIT:
                game->quitting = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) 
                {
                    case SDLK_UP:
                        // game->input.up = true;
                        // game->player.dy = -5;
                        if (move_player_if_possible(game, 0, -2)) {
                            game->input.up = true;
                            game->player.dy = -2;
                        } else {
                            game->player.dy = 0;

                        }
                        break;

                    case SDLK_DOWN:
                        // game->input.down = true;
                        // game->player.dy = 5;
                        if (move_player_if_possible(game, 0, 2)) {
                            game->input.down = true;
                            game->player.dy = 5;
                        } else {
                            game->player.dy = 0;

                        }
                        break;

                    case SDLK_LEFT:
                        // game->input.left = true;
                        // if (game->player.srcRect.y != 0 ) { player_change_animation(9, RUNNING_L, game); }
                        // game->player.dx = -2;
                        if (move_player_if_possible(game, -2, 0)) {
                            game->input.left = true;
                            if (game->player.srcRect.y != 0 ) { player_change_animation(9, RUNNING_L, game); }
                            game->player.dx = -2;
                        } else {
                            game->player.dx = 0;

                        }
                        break;

                    case SDLK_RIGHT:
                        // game->input.right = true;
                        // if (game->player.srcRect.y != 48 ) { player_change_animation(9, RUNNING_R, game); }
                        // game->player.dx = 2;
                        if (move_player_if_possible(game, 2, 0)) {
                            game->input.right = true;
                            if (game->player.srcRect.y != 48 ) { player_change_animation(9, RUNNING_R, game); }
                            game->player.dx = 2;                           
                        } else {
                            game->player.dx = 0;

                        }
                        break;

                    case SDLK_f: 
                        game->fullscreen = true;
                        toggle_fullscreen(game);
                        break;

                    case SDLK_ESCAPE:
                        game->quitting = true;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                // fallback to standing animation
                if (game->player.srcRect.y != STANDING_F ) { player_change_animation(1, STANDING_F, game);  }
                game->player.dx = 0;
                game->player.dy = 0;
                break;

            default:
                break;
        }
    }
}

bool move_player_if_possible(Game_t* game, int dx, int dy) {
    int original_x = game->player.srcRect.x;
    int original_y = game->player.srcRect.y;

    int temp_x = original_x + dx;
    int temp_y = original_y + dy;

    if (player_check_collision(game, temp_x, temp_y)) {
        // Reset to original position if collision detected
        game->player.srcRect.x = original_x;
        game->player.srcRect.y = original_y;
        return false;
    } else {
        // Update player's position if no collision
        game->player.srcRect.x = temp_x;
        game->player.srcRect.y = temp_y;
        return true;
    }
}
