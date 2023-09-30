
#ifndef makemap_h
#define makemap_h

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "cute_tiled.h"


struct  mymap{
    int map_width;
    int map_height;
    int layer_name;
    int *layer_data[3];
    int layer_length;
    int layer_id;
    char *tileset_name;
    int tileset_firstgid;
    int counter;
} ;

void free_map(struct mymap *m);
void process_map(SDL_Renderer* renderer, cute_tiled_map_t* mymap);
SDL_Texture* createLargeTexture(SDL_Renderer* renderer);

#endif /* makemap_h */
