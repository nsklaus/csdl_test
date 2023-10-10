#include "input.h"
#include <stdio.h>
#include "player.h"
#include "input.h"

static int temp_dx = 0;
static int temp_dy = 0;

SDL_Rect* will_collide(Game_t* game, int dx, int dy) {
    static SDL_Rect collidingTile;
    SDL_Rect predictedRect = game->player.dstRect;
    predictedRect.x += dx;
    predictedRect.y += dy;

    // check for collision only with nearby
    int playerGridX = (game->player.world_x + dx) / 16;
    int playerGridY = (game->player.world_y + dy) / 16;

    int playerSpanX = 48 / 16;
    int playerSpanY = 48 / 16;

    for (int y = playerGridY - playerSpanY; y <= playerGridY + playerSpanY; ++y) {
        for (int x = playerGridX - playerSpanX; x <= playerGridX + playerSpanX; ++x) {
            if (x >= 0 && x < game->map.width && y >= 0 && y < game->map.height) {
                if (SDL_HasIntersection(&predictedRect, &game->map.tile[y][x].rect)) {
                    collidingTile = game->map.tile[y][x].rect;
                    return &collidingTile;
                }
            }
        }
    }
    return NULL;
}

void toggle_fullscreen(Game_t* game) {
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool isFullscreen = SDL_GetWindowFlags(game->window) & fullscreenFlag;
    SDL_SetWindowFullscreen(game->window, isFullscreen ? 0 : fullscreenFlag);
    SDL_ShowCursor(isFullscreen);
}

void input_handle_events(Game_t* game) {
    SDL_Event event;

    // Update tile collision rectangles
    for (int y = 0; y < game->map.height; ++y) {
        for (int x = 0; x < game->map.width; ++x) {
            if(game->map.tile[y][x].solid) {
                game->map.tile[y][x].rect.x = (x * 16) - game->camera.x;
                game->map.tile[y][x].rect.y = (y * 16) - game->camera.y;
            }
        }
    }

    // Poll SDL Events
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->quitting = true;
                return;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        temp_dy = -2;
                        break;
                    case SDLK_DOWN:
                        temp_dy = 2;
                        break;
                    case SDLK_LEFT:
                        if (game->player.srcRect.y != RUNNING_L ) { player_change_animation(9, RUNNING_L, game); }
                        temp_dx = -2;
                        break;
                    case SDLK_RIGHT:
                        if (game->player.srcRect.y != RUNNING_R ) { player_change_animation(9, RUNNING_R, game); }
                        temp_dx = 2;
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
                            game->debug = !game->debug;
                            break;
                        }
                }
                break;

            case SDL_KEYUP:
                // fallbacl to default animation
                if (game->player.srcRect.y != STANDING_F ) { player_change_animation(1, STANDING_F, game);  }
                
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN:
                        temp_dy = 0;
                        break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        temp_dx = 0;
                        break;
                }
                break;
        }
    }

    // Perform collision check
    SDL_Rect* collidingTile = will_collide(game, temp_dx, temp_dy);

    if (!collidingTile) {
        game->player.dx = temp_dx;
        game->player.dy = temp_dy;
    } else {
        if (temp_dy < 0) {
            if (game->player.dstRect.y > collidingTile->y) {
                game->player.world_y = collidingTile->y + collidingTile->h + game->camera.y;
            }
        }
        game->player.dx = 0;
        game->player.dy = 0;
    }

    // Update the world position
    game->player.world_x += game->player.dx;
    game->player.world_y += game->player.dy;

    // Update the rendering position
    game->player.dstRect.x = game->player.world_x - game->camera.x;
    game->player.dstRect.y = game->player.world_y - game->camera.y;
}
