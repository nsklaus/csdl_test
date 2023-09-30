
#ifndef makemap_h
#define makemap_h

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "cute_tiled.h"
#include "game.h"


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

//struct Game; 

void free_map(struct mymap *m);
//void process_map(SDL_Renderer* renderer, const char* path);
SDL_Texture* createLargeTexture( Game* game, const char* path);

#endif /* makemap_h */
