//#include "game.h"
#define CUTE_TILED_IMPLEMENTATION
#include "cute_tiled.h" 
#include "makemap.h"
//LOG("Loading file %s", file);


SDL_Texture* createLargeTexture(Game* game, const char* path) 
{
    
    Map* tilemap = &game->tilemap;
    // Load the map file
    cute_tiled_map_t* map = cute_tiled_load_map_from_file(path, NULL);

    // Find the "foreground" layer

    cute_tiled_layer_t* tiled_layer = map->layers;
    
    //printf("\n layer width = %d\n",tiled_layer->width);
    tilemap->width = tiled_layer->width;
    tilemap->height = tiled_layer->height;
    //printf("\n game tilemap width = %d\n",tilemap->width);
    for (tiled_layer = map->layers; tiled_layer; tiled_layer = tiled_layer->next) {
        if (strcmp(tiled_layer->name.ptr, "foreground") == 0) {
            break;
        }
    }
    if (!tiled_layer) {
        printf("Foreground layer not found.\n");
        return NULL;
    }

    // Create a large image surface to hold the entire map
    SDL_Surface* largeImage = SDL_CreateRGBSurface(0, 80 * 16, 40 * 16, 32, 0, 0, 0, 0);

    // Load tileset
    SDL_Surface* tileset = IMG_Load("Assets/blueMetal.png");
    if (!tileset) {
        printf("Failed to load tileset.\n");
        return NULL;
    }

    for (int y = 0; y < 40; ++y) {
        for (int x = 0; x < 80; ++x) {
            int tileID = tiled_layer->data[y * 80 + x] - 1; // Adjusting for 0 index
            if (tileID >= 0) {
                SDL_Rect srcRect;
                srcRect.x = (tileID % 71) * 16; // 71 tiles per row in the tileset
                srcRect.y = (tileID / 71) * 16; // Calculate row based on tile ID
                srcRect.w = srcRect.h = 16;     // Each tile is 16x16 pixels

                SDL_Rect destRect;
                destRect.x = x * 16;
                destRect.y = y * 16;
                destRect.w = destRect.h = 16;

                SDL_BlitSurface(tileset, &srcRect, largeImage, &destRect);
            }
        }
    }

    // Convert the large image surface to texture
    SDL_Texture* largeTexture = SDL_CreateTextureFromSurface(game->renderer, largeImage);

    // Clean up
    SDL_FreeSurface(largeImage);
    SDL_FreeSurface(tileset);
    cute_tiled_free_map(map);

    return largeTexture;
}
