
#include "graphics.h"

void graphics_draw_rect(SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
}
