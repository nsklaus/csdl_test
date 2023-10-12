#include "input.h"
#include <SDL_scancode.h>
#include <stdio.h>
#include "player.h"

//static int temp_dx = 0;
//static int temp_dy = 0;
const float gravity = 0.1f;
const float jumpStrength = -5.0f;

// void apply_gravity(Game_t *game)
// {
//     game->player.feetRect.x = game->player.dstRect.x-16;
//     game->player.feetRect.y =  game->player.dstRect.y;
//     game->player.feetRect.w = 16;
//     game->player.feetRect.h = 16;
//     if(game->debug)
//     {
//         //printf("render feetrect.x=[%d][%d]\n",game->player.feetRect.x, game->player.feetRect.y);
//         // SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); // Set to red color
//         // SDL_RenderDrawRect(game->renderer, &game->player.feetRect);
//         // SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Reset color
//     }
// }

// void move_player(Game_t *game, int dx, int dy)
// {

// }


// bool will_collide(Game_t* game, int dx, int dy) 
// {
//     SDL_Rect predictedRect = game->player.dstRect;
//     predictedRect.x += dx;
//     predictedRect.y += dy;

//     SDL_Rect feetRect = predictedRect;
//     feetRect.y += predictedRect.h - 5;
//     feetRect.h = 5;

//     game->player.isGrounded = false;

//     for (int y = 0; y < game->map.height; ++y) 
//     {
//         for (int x = 0; x < game->map.width; ++x) 
//         {
//             SDL_Rect tileRect = game->map.tile[y][x].rect;
//             if (SDL_HasIntersection(&predictedRect, &tileRect)) 
//             {
//                 if (SDL_HasIntersection(&feetRect, &tileRect)) 
//                 {
//                     game->player.isGrounded = true;
//                     //printf("setting isGrounded to true: [%d]\n",game->player.isGrounded);
//                 }
//                 return true;
//             }
//         }
//     }
//     return false;
// }

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


    // ===================



    //apply_gravity(game);

    // ====================


    // Apply gravity
    // if (!game->player.isGrounded) 
    // { game->player.vy += gravity; } 
    // else 
    // { game->player.vy = 0; }


    // Poll SDL events
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
            //temp_dx = -1;
            game->player.dx = -2;
        }

        if (currentKeyStates[SDL_SCANCODE_RIGHT]) 
        {
            if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
            //temp_dx = 1;
            game->player.dx = 2;
        }
        if (currentKeyStates[SDL_SCANCODE_SPACE]) 
        {
            if (game->player.isGrounded) { game->player.vy = jumpStrength; }
        }
         
        if (currentKeyStates[SDL_SCANCODE_UP]) 
        {
            if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
            //temp_dy = -1;
            game->player.dy = -2;
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN]) 
        {
            if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
            //temp_dy = 1;
            game->player.dy = 2;
        }
    }

    // Perform collision check for horizontal movement
    // bool willCollideHorizontal = will_collide(game, temp_dx, 0);

    // if (!willCollideHorizontal) 
    // {
    //     game->player.dx = temp_dx;
    // } else {
    //     game->player.dx = 0;
    // }

    // Perform collision check for vertical movement
    // bool willCollideVertical = will_collide(game, 0, game->player.vy);

    // if (!willCollideVertical) 
    // {
    //     game->player.dy = game->player.vy;
    // } else {
    //     game->player.dy = 0;
    // }


}
