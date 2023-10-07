//#include "game.h"
#define CUTE_TILED_IMPLEMENTATION
#include "cute_tiled.h" 
#include "makemap.h"


SDL_Texture* createLargeTexture(Game* game, const char* path) 
{
    
    Map* map_t = &game->tilemap;
    // Load the map file
    cute_tiled_map_t* map = cute_tiled_load_map_from_file(path, NULL);

    // Find the "foreground" layer
    cute_tiled_layer_t* map_layer = map->layers;
    
    map_t->width = map_layer->width;
    map_t->height = map_layer->height;

    for (map_layer = map->layers; map_layer; map_layer = map_layer->next) {
        if (strcmp(map_layer->name.ptr, "foreground") == 0) {
            break;
        }
    }

    // Create a large image surface to hold the entire map
    SDL_Surface* largeImage = SDL_CreateRGBSurface(0, map_t->width * 16, map_t->height * 16, 32, 0, 0, 0, 0);

    // Load tileset
    SDL_Surface* tileset = IMG_Load("Assets/blueMetal.png");
    map_t->tileset_w = tileset->w;
    map_t->tileset_h = tileset->h;
    int row_length = map_t->tileset_w / 16; 

    for (int y = 0; y < map_t->height; ++y) {
        for (int x = 0; x < map_t->width; ++x) {
            int tileID = map_layer->data[y * map_t->width + x] - 1; // Adjusting for 0 index
            if (tileID >= 0) {
                SDL_Rect srcRect;
                srcRect.x = (tileID % row_length) * 16; // if zero then new row
                srcRect.y = (tileID / row_length) * 16; // calculate row based on tile ID
                srcRect.w = srcRect.h = 16;     // tilesize is 16x16

                SDL_Rect destRect;
                destRect.x = x * 16;
                destRect.y = y * 16;
                destRect.w = destRect.h = 16;

                SDL_BlitSurface(tileset, &srcRect, largeImage, &destRect);
            }
        }
    }

    // Convert surface to texture
    SDL_Texture* largeTexture = SDL_CreateTextureFromSurface(game->renderer, largeImage);

    // Clean up
    SDL_FreeSurface(largeImage);
    SDL_FreeSurface(tileset);
    cute_tiled_free_map(map);

    return largeTexture;
}


void createCollisionMap(Game* game, const char* path) {


}