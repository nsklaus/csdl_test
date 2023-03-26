//
//  object.c
//  mygame
//
//  Created by klaus on 24/03/2023.
//

#include "object.h"

Object* object_create(int x, int y, int w, int h, SDL_Color color) {
    Object* object = malloc(sizeof(Object));
    object->x = x;
    object->y = y;
    object->w = w;
    object->h = h;
    object->is_visible = true;
    object->color = color;
    return object;
}

void object_draw(SDL_Renderer* renderer, Object* object) {
    if (!object->is_visible) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, object->color.r, object->color.g, object->color.b, object->color.a);
    SDL_Rect rect = { object->x, object->y, object->w, object->h };
    SDL_RenderFillRect(renderer, &rect);
}

void object_destroy(Object* object) {
    free(object);
}
