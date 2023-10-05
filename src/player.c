#include "player.h"
#include <SDL_image.h>




Player player_init(Game* game) {
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
    player.frameCount = 1;
    player.currentFrame = 0;

    // Load the player's texture
    player.texture = IMG_LoadTexture(game->renderer, "Assets/samus.png");
    if (!player.texture) {
        //SDL_Log("Failed to load player texture: %s", SDL_GetError());
        printf("Failed to load player texture\n");
    }
    return player;
}

void player_update(Game* game) {
    // player.currentFrame++;
    // if (player.currentFrame >= player.frameCount) {
    //     player.currentFrame = 0;
    // }
    // player.srcRect.x = player.currentFrame * 48;
    game->player.currentFrame = 0;
}

void player_render(Game* game) {
    // if (player.texture) {
    //     SDL_RenderCopy(renderer, player.texture, &player.srcRect, &player.destRect);
    //     printf("bleh\n");
    // }
    if (!game->renderer) {
        SDL_Log("Player or renderer is NULL");
        return;
    }

    if (!game->player.texture) {
        SDL_Log("Player texture is NULL");
        return;
    }

    // Log the src_rect values to ensure they are correct
    // SDL_Log("src_rect - x: %d, y: %d, w: %d, h: %d", 
    //         game->player.srcRect.x, game->player.srcRect.y, 
    //         game->player.srcRect.w, game->player.srcRect.h);

    // Render the player texture
    int render_result = SDL_RenderCopy(game->renderer, game->player.texture, &game->player.srcRect, &game->player.destRect);

    if (render_result < 0) {
        SDL_Log("Failed to render player texture: %s", SDL_GetError());
    }

    // Ensure SDL_RenderPresent is called after rendering the player
    // This can be removed if SDL_RenderPresent is called elsewhere after rendering the player
    SDL_RenderPresent(game->renderer);
}

void player_change_animation(int frameCount, int yPosition, Game* game) {
    game->player.frameCount = frameCount;
    game->player.currentFrame = 0;
    game->player.srcRect.y = yPosition;
}

void player_destroy(Game* game) {
    if (game->player.texture) {
        SDL_DestroyTexture(game->player.texture);
        game->player.texture = NULL;
    }
}