#include "input.h"
#include <stdio.h>
#include "player.h"

static int temp_dx = 0;
//static int temp_dy = 0;
const float gravity = 0.1f;
const float jumpStrength = -5.0f;

bool will_collide(Game_t* game, int dx, int dy) {
    SDL_Rect predictedRect = game->player.dstRect;
    predictedRect.x += dx;
    predictedRect.y += dy;

    SDL_Rect feetRect = predictedRect;
    feetRect.y += predictedRect.h - 5;
    feetRect.h = 5;

    game->player.isGrounded = false;

    for (int y = 0; y < game->map.height; ++y) {
        for (int x = 0; x < game->map.width; ++x) {
            SDL_Rect tileRect = game->map.tile[y][x].rect;
            if (SDL_HasIntersection(&predictedRect, &tileRect)) {
                if (SDL_HasIntersection(&feetRect, &tileRect)) {
                    game->player.isGrounded = true;
                }
                return true;
            }
        }
    }
    return false;
}

void input_handle_events(Game_t* game) {
    SDL_Event event;

    // Update tile collision rectangles
    for (int y = 0; y < game->map.height; ++y) {
        for (int x = 0; x < game->map.width; ++x) {
            game->map.tile[y][x].rect.x = (x * 16) - game->camera.x;
            game->map.tile[y][x].rect.y = (y * 16) - game->camera.y;
        }
    }

    // Apply gravity
    if (!game->player.isGrounded) {
        game->player.vy += gravity;
    } else {
        game->player.vy = 0;
    }

    // Poll SDL events
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->quitting = true;
            return;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    if (game->player.srcRect.y != RUNNING_L ) { player_change_animation(9, RUNNING_L, game); }
                    temp_dx = -1;
                    break;
                case SDLK_RIGHT:
                    if (game->player.srcRect.y != RUNNING_R ) { player_change_animation(9, RUNNING_R, game); }
                    temp_dx = 1;
                    break;
                case SDLK_SPACE:
                    if (game->player.isGrounded) {
                        game->player.vy = jumpStrength;
                    }
                    break;
                case SDLK_d:
                    if (event.key.repeat == 0) 
                    {
                        game->debug = !game->debug;
                        break;
                    }
            }
        }
        if (event.type == SDL_KEYUP) {
            if (game->player.srcRect.y != STANDING_F ) { player_change_animation(1, STANDING_F, game);  }
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    temp_dx = 0;
                    break;
            }
        }
    }

    // Perform collision check for horizontal movement
    bool willCollideHorizontal = will_collide(game, temp_dx, 0);

    if (!willCollideHorizontal) {
        game->player.dx = temp_dx;
    } else {
        game->player.dx = 0;
    }

    // Perform collision check for vertical movement
    bool willCollideVertical = will_collide(game, 0, game->player.vy);

    if (!willCollideVertical) {
        game->player.dy = game->player.vy;
    } else {
        game->player.dy = 0;
    }

    // Update the world position
    game->player.world_x += game->player.dx;
    game->player.world_y += game->player.dy;

    // Update the rendering position
    game->player.dstRect.x = game->player.world_x - game->camera.x;
    game->player.dstRect.y = game->player.world_y - game->camera.y;
}
