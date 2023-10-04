#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    int frameCount;
    int currentFrame;
    SDL_Texture* texture;
} Player;

void player_init(SDL_Renderer* renderer, Player player);
void player_update(Player player);
void player_render(SDL_Renderer* renderer,Player player);
void player_change_animation(int frameCount, int yPosition,Player player);
void player_destroy(Player player);

#endif // PLAYER_H