#include "make_map.h"

SDL_Surface *process_map(struct mymap *map){

    SDL_Rect srcrect = { 0, 0, 16, 16 };
    SDL_Rect dstrect = { 0, 0, 16, 16 };
    int width = map->map_width*16;
    int height = map->map_height*16;

    SDL_Surface * map_img =
	SDL_CreateRGBSurface(0, width, height, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    SDL_Surface * image = IMG_Load("assets/blueMetal.png");
    if(!image) exit(1);
    //SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    // loop around mymap struct elements built map, call render:
    for (int i = 0; i < map->layer_length; i++){
        int cur_id = map->layer_data[0][i]; // get value of tiled
        int ts_x = cur_id/71; // find x coords on tileset
        int ts_y = cur_id % 71; // find y 
        
        srcrect.x = ts_x*16; // start cutting at said coords on tileset
        srcrect.y = ts_y*16;

        dstrect.x =  i * 16; // place the tile that have been cut on the render surface according to vlue of 'i'
        if (i % 80 == 0){
            dstrect.y = i * 16;
            dstrect.x = 0;
        }

	// HACK HACK, to get something onto the display and check we're on
         // right path
        if(i == 0) {srcrect.x = 0; srcrect.y = 0; }

        if(SDL_BlitSurface(image, &srcrect, map_img, &dstrect))
		fprintf(stderr, "%s\n", SDL_GetError());
        //render(texture, &srcrect, &dstrect);
    }
    return map_img;
}
