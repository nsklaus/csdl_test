#include "make_map.h"


// testing passing mymap struct around
void process_map(struct mymap *map){

    // testing printing values to confirm we still have data it should have get filled with
    // printf("map value layer[2][254] = %d\n", map->layer_data[2][254]);
    // printf("map value layer[1][335] = %d\n", map->layer_data[1][335]);
    // printf("map value layer[0][0] = %d\n", map->layer_data[0][0]); 
    // works

    int x = 0;
    int y = 0;
    SDL_Rect srcrect = { 0, 0, 16, 16 };
    SDL_Rect dstrect = { x, y, 16, 16 };
    SDL_Surface * image = IMG_Load("assets/bluemetal.png");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    // loop around mymap struct elements built map, call render:
    for (int i = 0; i < map->layer_length; i++){
        x = i * 16;
        if (i % 80 == 0){
            y = i * 16;
            x = 0;
        }
        render(texture, &srcrect, &dstrect);
    }
}