#include "input.h"
#include <SDL2/SDL_scancode.h>
#include <stdio.h>
#include "player.h"

// const float gravity = 0.1f;
 const float jumpStrength = -5.0f;


void toggle_fullscreen(Game_t* game) 
{
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool isFullscreen = SDL_GetWindowFlags(game->window) & fullscreenFlag;
    SDL_SetWindowFullscreen(game->window, isFullscreen ? 0 : fullscreenFlag);
    SDL_ShowCursor(isFullscreen);
}

void input_update(Game_t* game) 
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) 
    {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (event.type == SDL_QUIT) 
        {
            game->quitting = true;
            return;
        }

        if (event.type == SDL_KEYDOWN) 
        {
            switch (event.key.keysym.sym) 
            {
                case SDLK_d:
                    if (event.key.repeat == 0) 
                    { 
                        game->debug = !game->debug;
                    }
                    break;

                case SDLK_f: 
                    game->fullscreen = true;
                    toggle_fullscreen(game);
                    break;
            }
        }
        if (event.type == SDL_KEYUP) 
        {
            if (game->player.srcRect.y != STANDING_F ) { player_animation(1, STANDING_F, game); }
            game->player.dx = 0;
            game->player.dy = 0;
        }

        if (currentKeyStates[SDL_SCANCODE_LEFT]) 
        {
            if (game->player.srcRect.y != RUNNING_L ) { player_animation(9, RUNNING_L, game); }
            game->player.left = true;
            move(game, -2,0);
        }

        if (currentKeyStates[SDL_SCANCODE_RIGHT]) 
        {
            if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
            game->player.right = true;
            move(game, 2,0);
        }

        if (currentKeyStates[SDL_SCANCODE_UP]) 
        {
            if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
            game->player.up = true;
            move(game, 0,-2);
        }

        if (currentKeyStates[SDL_SCANCODE_DOWN]) 
        {
            if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
            game->player.down = true;
            move(game, 0,2);
        }

        if (currentKeyStates[SDL_SCANCODE_SPACE]) 
        {
            if (game->player.isGrounded) { game->player.vy = jumpStrength; }
        }
    }
}

bool blocked;
void move(Game_t* game, int dx, int dy) 
{
    int counter =0;
    SDL_Rect predictedRect = game->player.dstRect;
    predictedRect.x += dx;
    predictedRect.y += dy;
    blocked = false;
    // for (int y = 0; y < game->map.height; ++y) 
    // {
    //     for (int x = 0; x < game->map.width; ++x) 
    //     {
    //         if(game->map.tile[y][x].solid)
    //         {
    //             counter+=1;
    //             SDL_Rect tileRect = game->map.tile[y][x].rect;
    //             if (SDL_HasIntersection(&predictedRect, &tileRect)) 
    //             {
    //                 printf("collision\n");
    //                 blocked = true;
    //             }
    //         }
    //     }
    // }

    int playerGridX = (game->player.world_x + dx) / 16;
    int playerGridY = (game->player.world_y + dy) / 16;

    int playerSpanX = 48 / 16;
    int playerSpanY = 48 / 16;

    for (int y = playerGridY - playerSpanY; y <= playerGridY + playerSpanY; ++y) 
    {
        for (int x = playerGridX - playerSpanX; x <= playerGridX + playerSpanX; ++x) 
        {
            if (x >= 0 && x < game->map.width && y >= 0 && y < game->map.height) 
            {
                counter+=1;
                if (SDL_HasIntersection(&predictedRect, &game->map.tile[y][x].rect)) 
                {
                    printf("collision\n");
                    printf("player.world_y=[%d] +dy=[%d] /16 = %d \n",game->player.world_y, dy, playerGridY);
                    blocked=true;
                }
            }
            SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255); // Set color to red for debugging
            SDL_RenderDrawRect(game->renderer, &game->map.tile[y][x].rect);
            SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Reset color
        }
    }

    printf("counter=[%d]\n", counter);
    if(!blocked)
    {
        game->player.dx = dx;
        game->player.dy = dy;
    }
}
