#include "player.h"
#include <SDL_image.h>

// Initialize world coordinates
int world_x = 0, world_y = 0;

Player player_init(Game* game) 
{
    Player player;
    player.x = 48;
    player.y = 48;
    player.srcRect.w = 48;
    player.srcRect.h = 48;
    player.srcRect.x = 0;
    player.srcRect.y = 0;
    player.destRect.w = 48;
    player.destRect.h = 48;
    player.destRect.x = player.x;
    player.destRect.y = player.y;
    player.frameCount = 9;
    player.currentFrame = 0;

    // Load the player's texture
    player.texture = IMG_LoadTexture(game->renderer, "Assets/samus.png");
    if (!player.texture) {
        //SDL_Log("Failed to load player texture: %s", SDL_GetError());
        printf("Failed to load player texture\n");
    }
    return player;
}


void player_update(Game* game, float deltaTime) 
{
    // Update world coordinates based on input
    game->player.world_x += game->player.dx;
    game->player.world_y += game->player.dy;

    game->player.currentFrame += 10.0f * deltaTime;  // 10.0f is the speed of the animation
    if (game->player.currentFrame >= game->player.frameCount) {
        game->player.currentFrame -= game->player.frameCount;
    }
    game->player.srcRect.x = (int)game->player.currentFrame * 48;
}


void player_render(Game* game) 
{
    // Render the player texture
    SDL_RenderCopy(game->renderer, game->player.texture, &game->player.srcRect, &game->player.destRect);
}

void player_change_animation(int frameCount, int yPosition, Game* game) 
{
    game->player.frameCount = frameCount;
    game->player.currentFrame = 0;
    game->player.srcRect.y = yPosition;
}

void player_destroy(Game* game) 
{
    if (game->player.texture) 
    {
        SDL_DestroyTexture(game->player.texture);
        game->player.texture = NULL;
    }
}