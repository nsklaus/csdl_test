#include <SDL.h>

void renderPlayer(SDL_Renderer* renderer) {
    const int TILE_WIDTH = 48;
    const int TILE_HEIGHT = 48;

    SDL_Rect srcRect = {
        player->currentFrame * TILE_WIDTH,
        player->currentState * TILE_HEIGHT,
        TILE_WIDTH,
        TILE_HEIGHT
    };

    SDL_Rect destRect = {
        player->x,
        player->y,
        TILE_WIDTH,
        TILE_HEIGHT
    };

    SDL_RenderCopy(renderer, player->texture, &srcRect, &destRect);
}