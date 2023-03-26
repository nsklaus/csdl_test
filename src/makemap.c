
#include "makemap.h"
#define CUTE_TILED_IMPLEMENTATION
#include "cute_tiled.h"


SDL_Surface *process_map(struct mymap *map) {
    
    SDL_Rect srcrect = { 0, 0, 16, 16 };
    SDL_Rect dstrect = { 0, 0, 16, 16 };
    int width = map->map_width * 16;
    int height = map->map_height * 16;

    SDL_Surface * map_img = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_Surface * image = IMG_Load("assets/blueMetal.png");
    
    if(!image)
        exit(1);

    int ts_x = 0;
    int ts_y = 0;
    // loop around mymap struct elements built map, call render:
    for ( int i = 0; i < map->layer_length; i++ ){
        int cur_id = map->layer_data[0][i]; // get value of tiled

        if (cur_id != 0) {
            ts_x = (cur_id -1) % 71; // find x coords on tileset
            ts_y = (cur_id -1) / 71; // find y coords on tileset
            srcrect.x = ts_x * 16; // start cutting at said coords on tileset
            srcrect.y = ts_y * 16;
        } else {
            srcrect.x = 6*16; // manualy select an empty tile from tileset
            srcrect.y = 0;
        }

        dstrect.x += 16;
        if (i % 80 == 0){   // if i mod 80 = 0 it means new line
            dstrect.y = (i / 80) * 16;
            dstrect.x = 0;
        }

        if(SDL_BlitSurface(image, &srcrect, map_img, &dstrect))
            fprintf(stderr, "%s\n", SDL_GetError());
    }
    
    
    cute_tiled_map_t* mymap;
    mymap = cute_tiled_load_map_from_file("/Users/klaus/Sources/mygame/Assets/level01.json", NULL);
    fprintf(stderr, "map=%d\n",mymap->width);
    
    union cute_tiled_string_t my_union;
    my_union.ptr = mymap->layers->name.ptr;
    printf("layer name = %s \n", my_union.ptr);
    
    cute_tiled_layer_t* layer = mymap->layers;
    while (layer != NULL) {
        printf("Layer name: %s\n", layer->name.ptr);
        layer = layer->next;
    }
    SDL_FreeSurface(image);
    return map_img;
}

