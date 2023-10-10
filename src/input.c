#include "input.h"
#include <stdio.h>
#include "player.h"
#include "input.h"

int isDKeyPressed = 0;

void toggle_fullscreen(Game_t* game) {
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool isFullscreen = SDL_GetWindowFlags(game->window) & fullscreenFlag;
    SDL_SetWindowFullscreen(game->window, isFullscreen ? 0 : fullscreenFlag);
    SDL_ShowCursor(isFullscreen);
}



void check_collision(Game_t* game, const char* go) {

    game->player.dx = 0;
    game->player.dy = 0;
    // Calculate the grid cell the player is in
    int playerGridX = game->player.world_x / 16;
    int playerGridY = game->player.world_y / 16;

    // Calculate how many tiles the player could span (player size / tile size)
    int playerSpanX = 48 / 16;
    int playerSpanY = 48 / 16;

    bool collides = false;
    //int counter = 0;
    // Loop over the cells that the player could potentially intersect with
    for (int y = playerGridY - playerSpanY; y <= playerGridY + playerSpanY; ++y) 
    {
        for (int x = playerGridX - playerSpanX; x <= playerGridX + playerSpanX; ++x) 
        {
            //counter+=1;
            // Make sure we're not out of bounds
            if (x >= 0 && x < game->map.width && y >= 0 && y < game->map.height) 
            {
                // Update and check tile as before
                game->map.tile[y][x].rect.x = (x * 16) - game->camera.x;
                game->map.tile[y][x].rect.y = (y * 16) - game->camera.y;
                
                if (SDL_HasIntersection(&game->player.dstRect, &game->map.tile[y][x].rect)) 
                {
                    printf(" Collision detected \n");
                    
                    collides = true;
                    break;
                }
            }
        }
        if (collides) break;
    }
    if (!collides) {
        //printf("counter=[%d]\n", counter);
        //return false;  // No collision
        if (strcmp(go, "up") == 0)
        {
            game->player.dy = -2;
        }
        if (strcmp(go, "down") == 0)
        {
            game->player.dy = 2;
        }
        if (strcmp(go, "left") == 0)
        {
            game->player.dx = -2;
        }
        if (strcmp(go, "right") == 0)
        {
            game->player.dx = 2;
        }

    }
}


void input_handle_events(Game_t* game) {
    SDL_Event event;
    game->input.up = false;
    game->input.down = false;
    game->input.left = false;
    game->input.right = false;
    game->quitting = false;
    game->fullscreen = false;
    

    // update collision rectangles positions when map scrolls
    for (int y = 0; y < game->map.height; ++y) 
    {
        for (int x = 0; x < game->map.width; ++x) 
        {
            if(game->map.tile[y][x].solid)
            {
                game->map.tile[y][x].rect.x = (x * 16) - game->camera.x;
                game->map.tile[y][x].rect.y = (y * 16) - game->camera.y;
            }
        }
    }
    game->player.dstRect.x = game->player.world_x - game->camera.x;
    game->player.dstRect.y = game->player.world_y - game->camera.y;

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
                        // if (!check_collision(game, game->player.dstRect.x, game->player.dstRect.y - 2)) {
                        //     game->player.dy = -2;
                        // }
                        check_collision(game, "up");
                        break;

                    case SDLK_DOWN:
                        // if (!check_collision(game, game->player.dstRect.x, game->player.dstRect.y + 2)) {
                        //     game->player.dy = 2;
                        // }
                        check_collision(game, "down");
                        break;

                    case SDLK_LEFT:
                        // if (!check_collision(game, game->player.dstRect.x - 2, game->player.dstRect.y)) {
                        //     game->player.dx = -2;
                        // }
                        if (game->player.srcRect.y != RUNNING_L ) { player_change_animation(9, RUNNING_L, game); }
                        check_collision(game, "left");
                        break;

                    case SDLK_RIGHT:
                        // if (!check_collision(game, game->player.dstRect.x + 2, game->player.dstRect.y)) {
                        //     game->player.dx = 2;
                        // }
                        if (game->player.srcRect.y != RUNNING_R ) { player_change_animation(9, RUNNING_R, game); }
                        check_collision(game, "right");
                        break;

                    case SDLK_f:
                        game->fullscreen = true;
                        toggle_fullscreen(game);
                        break;

                    case SDLK_ESCAPE:
                        game->quitting = true;
                        break;

                    case SDLK_d:
                        if (event.key.repeat == 0) 
                        {
                            printf("\n");

                            for (int y = 0; y < game->map.height; ++y) 
                            {
                                for (int x = 0; x < game->map.width; ++x) 
                                {
                                    if(game->map.tile[y][x].solid)
                                    {
                                        printf("tileAt[%d][%d]\n",game->map.tile[y][x].rect.x, game->map.tile[y][x].rect.y);
                                    }
                                }
                            }

                            printf("\nplayercam[%d][%d]\n",game->camera.x, game->camera.y);
                            printf("playerdst[%d][%d]\n",game->player.dstRect.x, game->player.dstRect.y);
                            printf("playerwor[%d][%d]\n",game->player.world_x, game->player.world_y);
                        }
                        break;

                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                if (game->player.srcRect.y != STANDING_F ) { player_change_animation(1, STANDING_F, game);  }
                game->player.dx = 0;
                game->player.dy = 0;
                isDKeyPressed = 0;
                break;

            default:
                break;
        }
    }
}
