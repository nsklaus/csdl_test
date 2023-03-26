
#ifndef makemap_h
#define makemap_h

#include "game.h"
#include <stdio.h>

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
//struct mymap* load_map(char* filename);
void free_map(struct mymap *m);
SDL_Surface *process_map(struct mymap *map);

#endif /* makemap_h */
