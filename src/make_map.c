#include "make_map.h"

SDL_Surface *process_map(struct mymap *map){

    SDL_Rect srcrect = { 0, 0, 16, 16 };
    SDL_Rect dstrect = { 0, 0, 16, 16 };
    int width = map->map_width * 16;
    int height = map->map_height * 16;

    SDL_Surface * map_img =
	SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

    SDL_Surface * image = IMG_Load("assets/blueMetal.png");
    if(!image) 
        exit(1);
    int ts_x = 0;
    int ts_y = 0;
    // loop around mymap struct elements built map, call render:
    for ( int i = 0; i < map->layer_length; i++ ){
        int cur_id = map->layer_data[0][i]; // get value of tiled

        if (cur_id != 0) {
            int ts_x = (cur_id -1) % 71; // find x coords on tileset
            int ts_y = (cur_id -1) / 71; // find y coords on tileset       
            srcrect.x = ts_x * 16; // start cutting at said coords on tileset
            srcrect.y = ts_y * 16;
        } else {
            srcrect.x = 6*16;
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
    return map_img;
}
