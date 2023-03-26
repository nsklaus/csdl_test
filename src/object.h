//
//  object.h
//  mygame
//
//  Created by klaus on 24/03/2023.
//


#ifndef OBJECT_H
#define OBJECT_H


#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
    int w;
    int h;
    bool is_visible;
    SDL_Color color;
} Object;

Object* object_create(int x, int y, int w, int h, SDL_Color color);
void object_draw(SDL_Renderer* renderer, Object* object);
void object_destroy(Object* object);

#endif // OBJECT_H
