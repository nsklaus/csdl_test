#include "player.h"
#include <SDL_image.h>




void player_init(SDL_Renderer* renderer, Player player) {
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
    player.frameCount = 1;
    player.currentFrame = 0;

    // Load the player's texture
    player.texture = IMG_LoadTexture(renderer, "Assets/samus.png");
    if (!player.texture) {
        SDL_Log("Failed to load player texture: %s", SDL_GetError());
    }
}

void player_update(Player player) {
    // player.currentFrame++;
    // if (player.currentFrame >= player.frameCount) {
    //     player.currentFrame = 0;
    // }
    // player.srcRect.x = player.currentFrame * 48;
    player.currentFrame = 0;
}

void player_render(SDL_Renderer* renderer, Player player) {
    if (player.texture) {
        SDL_RenderCopy(renderer, player.texture, &player.srcRect, &player.destRect);
        printf("bleh\n");
    }
}

void player_change_animation(int frameCount, int yPosition, Player player) {
    player.frameCount = frameCount;
    player.currentFrame = 0;
    player.srcRect.y = yPosition;
}

void player_destroy(Player player) {
    if (player.texture) {
        SDL_DestroyTexture(player.texture);
        player.texture = NULL;
    }
}