#include "input.h"
#include <stdio.h>

void toggle_fullscreen(Game* game) {  // Added this function
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool isFullscreen = SDL_GetWindowFlags(game->window) & fullscreenFlag;

    SDL_SetWindowFullscreen(game->window, isFullscreen ? 0 : fullscreenFlag);
    SDL_ShowCursor(isFullscreen);
}

void input_handle_events(Game* game) 
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
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->quitting = true;
                printf("Quit event detected.\n");
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        game->input.up = true;
                        //printf("Up key pressed.\n");
                        if (game->camera.y > 0)
                        {
                            game->camera.y -= game->camera.speed;
                        }
printf("\n going up. camY[%d], mapH[%d], gameH[%d]\n",game->camera.y, game->tilemap.height * 16, game->height);

                        break;
                    case SDLK_DOWN:
                        game->input.down = true;
                        //printf("Down key pressed.\n");
                        if (game->camera.y < (game->tilemap.height * 16 - game->height))
                        {
                            game->camera.y += game->camera.speed;
                        }
printf("\n going down. camY[%d], mapH[%d], gameH[%d]\n",game->camera.y, game->tilemap.height * 16, game->height);
                        break;
                    case SDLK_LEFT:
                        game->input.left = true;
                        //printf("Left key pressed.\n");
                        if (game->camera.x > 0)
                        {
                            game->camera.x -= game->camera.speed;
                        }
printf("\n going right. camX[%d], mapW[%d], gameW[%d]\n",game->camera.x, game->tilemap.width * 16, game->width);
                        break;
                    case SDLK_RIGHT:
                        game->input.right = true;
                        //printf("Right key pressed.\n");
                        if (game->camera.x < game->tilemap.width * 16 - game->width) 
                        {
                            game->camera.x += game->camera.speed;
                        }
printf("\n going right. camX[%d], mapW[%d], gameW[%d]\n",game->camera.x, game->tilemap.width * 16, game->width);

                        break;
                    case SDLK_f:  // Added this case to handle fullscreen toggle
                        game->fullscreen = true;
                        //printf("F key pressed \n");
                        toggle_fullscreen(game);
                        break;
                    case SDLK_ESCAPE:
                        game->quitting = true;
                        //printf("Escape key pressed.\n");
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                // Handle key up events if needed
                break;
            default:
                break;
        }
    }
}
