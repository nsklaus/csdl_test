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

    player.destRect.x = 0;          // screen coords 
    player.destRect.y = 0;
    player.destRect.w = TILESIZE;
    player.destRect.h = TILESIZE;

    player.frameCount = 1;          // initial animation number of frames
    player.currentFrame = 0; 

    // Load the player's texture
    player.texture = IMG_LoadTexture(game->renderer, "Assets/samus.png");
    return player;
}


void player_update(Game_t* game, float deltaTime) 
{

    // // Store old position
    // int old_x = game->player.world_x;
    // int old_y = game->player.world_y;

    // // Update world coordinates based on input
    // game->player.world_x += game->player.dx;
    // game->player.world_y += game->player.dy;

    // // Update destination rectangle for collision check
    // game->player.destRect.x = game->player.world_x - game->camera.x;
    // game->player.destRect.y = game->player.world_y - game->camera.y;

    // // Check for collision
    // if (player_check_collision(game)) {
    //     // Revert to old position
    //     game->player.world_x = old_x;
    //     game->player.world_y = old_y;
    // }

    // Update world coordinates based on input
    game->player.world_x += game->player.dx;
    game->player.world_y += game->player.dy;

    game->player.currentFrame += 10.0f * deltaTime;  // 10.0f is the speed of the animation
    if (game->player.currentFrame >= game->player.frameCount) {
        game->player.currentFrame -= game->player.frameCount;
    }
    game->player.srcRect.x = (int)game->player.currentFrame * 48;
    

}

// void move_player(Game_t* game, int dx, int dy) {
//   game->player.srcRect.x += dx;
//   game->player.srcRect.y += dy;
// }

// bool player_check_collision(Game_t* game, int temp_x, int temp_y) {
//     SDL_Rect tempRect = game->player.srcRect;
//     tempRect.x = temp_x;
//     tempRect.y = temp_y;
//     for (int y = 0; y < game->map.height; ++y) {
//         for (int x = 0; x < game->map.width; ++x) {
//             if (game->map.collide[y][x].solid) {
//                 SDL_Rect* rect = &game->map.collide[y][x].rect;
//                 if (SDL_HasIntersection(rect, &tempRect)) {  // Changed from destRect to tempRect
//                     printf("Collision detected at x=%d, y=%d\n", temp_x, temp_y);  // Debug 
//                     return true;
//                 }
//             }
//         }
//     }
//     printf("No collision at x=%d, y=%d\n", temp_x, temp_y);  // Debug 
//     return false;
// }

void player_render(Game_t* game) 
{
    // Render the player texture
    game->player.destRect.x = game->player.world_x - game->camera.x;
    game->player.destRect.y = game->player.world_y - game->camera.y;
    SDL_RenderCopy(game->renderer, game->player.texture, &game->player.srcRect, &game->player.destRect);
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