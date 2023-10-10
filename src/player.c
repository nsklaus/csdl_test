#include "player.h"
#include <SDL_image.h>

// Initialize world coordinates
//int world_x = 0, world_y = 0;


Player_t player_init(Game_t* game) 
{
    Player_t player;
    player.world_x = 150;           // initial position in game coords
    player.world_y = 176;

    player.srcRect.x = 0;           // cutting in spritesheet
    player.srcRect.y = STANDING_F;  // standing sprite (6th row)
    player.srcRect.w = TILESIZE; 
    player.srcRect.h = TILESIZE;

    player.dstRect.x = 0;          // screen coords 
    player.dstRect.y = 0;
    player.dstRect.w = TILESIZE;
    player.dstRect.h = TILESIZE;

    player.frameCount = 1;          // initial animation number of frames
    player.currentFrame = 0; 

    // Load the player's texture
    player.texture = IMG_LoadTexture(game->renderer, "Assets/samus.png");
    return player;
}


void player_update(Game_t* game, float deltaTime) 
{

    // Store old position
    // int old_x = game->player.world_x;
    // int old_y = game->player.world_y;

    // // Calculate new position based on input
    // int new_x = game->player.world_x + game->player.dx;
    // int new_y = game->player.world_y + game->player.dy;

    // // Check for collision at the new position
    // if (check_collision(game, new_x, new_y)) {
    //     // Collision detected, revert to old position
    //     game->player.world_x = old_x;
    //     game->player.world_y = old_y;
    // } else {
    //     // No collision, update the position
    //     game->player.world_x = new_x;
    //     game->player.world_y = new_y;
    // }

    // Update world coordinates based on input
    game->player.world_x += game->player.dx;
    game->player.world_y += game->player.dy;

    game->player.currentFrame += 10.0f * deltaTime;  // 10.0f is the speed of the animation
    if (game->player.currentFrame >= game->player.frameCount) {
        game->player.currentFrame -= game->player.frameCount;
    }
    game->player.srcRect.x = (int)game->player.currentFrame * 48;

    //if (SDL_HasIntersection(game->player.srcRect
    //printf("player pos=[%d][%d]\n",game->player.world_x,game->player.world_y);
}

void player_render(Game_t* game) 
{
    // Render the player texture
    // game->player.dstRect.x = game->player.world_x - game->camera.x;
    // game->player.dstRect.y = game->player.world_y - game->camera.y;
    SDL_RenderCopy(game->renderer, game->player.texture, &game->player.srcRect, &game->player.dstRect);
}

// how much frames for a given anim type
void player_change_animation(int frameCount, AnimationType animType, Game_t* game) 
{
    game->player.frameCount = frameCount;
    game->player.srcRect.y = animType;
}

void player_destroy(Game_t* game) 
{
    if (game->player.texture) 
    {
        SDL_DestroyTexture(game->player.texture);
        game->player.texture = NULL;
    }
}