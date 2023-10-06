#include "player.h"
#include <SDL_image.h>

// Initialize world coordinates
//int world_x = 0, world_y = 0;

Player player_init(Game* game) 
{
    Player player;
    player.world_x = 150;   // initial position in game coords
    player.world_y = 176;

    player.srcRect.x = 0;   // cutting in spritesheet
    player.srcRect.y = 288; // standing sprite (6th row)
    player.srcRect.w = 48; 
    player.srcRect.h = 48;

    player.destRect.x = 0;  // screen coords 
    player.destRect.y = 0;
    player.destRect.w = 48;
    player.destRect.h = 48;

    player.frameCount = 1;  // initial animation number of frames
    player.currentFrame = 0; 

    // Load the player's texture
    player.texture = IMG_LoadTexture(game->renderer, "Assets/samus.png");
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
    game->player.destRect.x = game->player.world_x - game->camera.x;
    game->player.destRect.y = game->player.world_y - game->camera.y;
    SDL_RenderCopy(game->renderer, game->player.texture, &game->player.srcRect, &game->player.destRect);
}

void player_change_animation(int frameCount, int yPosition, Game* game) 
{
    game->player.frameCount = frameCount;
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