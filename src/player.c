#include "player.h"
#include <SDL2/SDL_image.h>

void player_init(Game_t* game) 
{
    game->player.world_x = 150;           // initial position
    game->player.world_y = 176;

    game->player.srcRect.x = 0;           // cutting in spritesheet
    game->player.srcRect.y = STANDING_F;  // standing sprite (6th row)
    game->player.srcRect.w = TILESIZE; 
    game->player.srcRect.h = TILESIZE;

    game->player.dstRect.x = 0;           // screen coords 
    game->player.dstRect.y = 0;
    game->player.dstRect.w = TILESIZE;
    game->player.dstRect.h = TILESIZE;

    game->player.frameCount = 1;          // initial animation number of frames
    game->player.currentFrame = 0; 

    // Load the player's texture
    game->player.texture = IMG_LoadTexture(game->renderer, "assets/samus.png");
}

void player_update(Game_t* game, float deltaTime) 
{
    // animation
    game->player.currentFrame += 10.0f * deltaTime;  // 10.0f is the speed of the animation
    if (game->player.currentFrame >= game->player.frameCount) {
        game->player.currentFrame -= game->player.frameCount;
    }
    game->player.srcRect.x = (int)game->player.currentFrame * 48;

    // move map according to player position
    if (game->player.world_x > game->width / 2) {
        game->camera.x = game->player.world_x - game->width / 2;
        if (game->camera.x + game->width > game->map.width * 16) {
            game->camera.x = game->map.width * 16 - game->width;
        }
    }
    if (game->player.world_y > game->height / 2) {
        game->camera.y = game->player.world_y - game->height / 2;
        if (game->camera.y + game->height > game->map.height * 16 ) {
            game->camera.y = game->map.height * 16 - game->height;
        }
    }

    // Update world offset based on player position
    game->player.world_x += game->player.dx;
    game->player.world_y += game->player.dy;

    // Update the rendering position
    game->player.dstRect.x = game->player.world_x - game->camera.x;
    game->player.dstRect.y = game->player.world_y - game->camera.y;

    // wip: player additional collision rectangles
    game->player.feetRect.x = game->player.dstRect.x-16;
    game->player.feetRect.y =  game->player.dstRect.y;
    game->player.feetRect.w = 16;
    game->player.feetRect.h = 16;
}


void move(Game_t* game, int dx, int dy) 
{
    //int counter =0;
    SDL_Rect predictedRect = game->player.dstRect;
    predictedRect.x += dx;
    predictedRect.y += dy;
    predictedRect.w += 1;
    predictedRect.h += 1;
    //blocked = false;

    int playerGridX = (game->player.world_x + 16 ) / 16;
    int playerGridY = (game->player.world_y + 16) / 16;

    int playerSpanX = 64 / 16;
    int playerSpanY = 64 / 16;
    int counter=0;
    //game->player.blocked = true;
    //printf("blocked=[%d], p.dstR.x=[%d], predR.x=[%d]\n", game->player.blocked, game->player.dstRect.x, predictedRect.x);
    for (int y = playerGridY - playerSpanY; y <= playerGridY + playerSpanY; y++) 
    {
        for (int x = playerGridX - playerSpanX; x <= playerGridX + playerSpanX; x++) 
        {
            if (SDL_HasIntersection(&predictedRect, &game->map.tile[y][x].rect)) 
            {
                counter+=1;
                printf("blocked=[%d] collision [%d]\n", game->player.blocked, counter);
                game->player.blocked = true;
            }
            // SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255); // Set color to red for debugging
            // SDL_RenderDrawRect(game->renderer, &game->map.tile[y][x].rect);
            // SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);   // Reset color
        }
    }

    if(!game->player.blocked)
    {
        game->player.world_x += dx;
        game->player.world_y += dy;
    }
}

void player_render(Game_t* game) 
{
    SDL_RenderCopy(game->renderer, game->player.texture, &game->player.srcRect, &game->player.dstRect);
    if (!game->player.blocked)
    {
        if (game->player.up)    { move( game,  0, -2); }
        if (game->player.down)  { move( game,  0,  2); }
        if (game->player.left)  { move( game, -2,  0); }
        if (game->player.right) { move( game,  2,  0); }
    }
    if (game->debug)
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); // Set color to red for debugging
        //SDL_RenderDrawRect(game->renderer, &game->player.feetRect);
        SDL_RenderDrawRect(game->renderer, &game->player.dstRect);
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Reset color
    }
}

// how much frames for a given anim type
void player_animation(int frameCount, AnimationType animType, Game_t* game) 
{
    game->player.frameCount = frameCount;
    game->player.srcRect.y = animType;
}

void player_destroy(Game_t* game) 
{
    SDL_DestroyTexture(game->player.texture);
    game->player.texture = NULL;
}