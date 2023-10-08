//#include "game.h"
#include <SDL_rect.h>
#define CUTE_TILED_IMPLEMENTATION
#include "cute_tiled.h" 
#include "makemap.h"


//SDL_Texture* createLargeTexture(Game* game, const char* path) 
void createLargeTexture(Game_t* game, const char* path) 
{
    
    Map_t* map = &game->map;
    // Load the map file
    cute_tiled_map_t* tmap = cute_tiled_load_map_from_file(path, NULL);

    // Find the "foreground" layer
    cute_tiled_layer_t* map_layer = tmap->layers;
    
    map->width = map_layer->width;
    map->height = map_layer->height;

    for (map_layer = tmap->layers; map_layer; map_layer = map_layer->next) 
    {

        if (strcmp(map_layer->name.ptr, "foreground") == 0) 
        {

            // Create a large image surface to hold the entire map
            SDL_Surface* largeImage = SDL_CreateRGBSurface(0, map->width * 16, map->height * 16, 32, 0, 0, 0, 0);

            // Load tileset
            //SDL_Surface* tileset = IMG_Load("Assets/blueMetal.png");
            char *buffer;
            asprintf(&buffer, "Assets/%s", tmap->tilesets->image.ptr);
            //printf("tileset=[%s]\n",buffer);
            
            SDL_Surface* tileset = IMG_Load(buffer);
            free(buffer);

            map->tileset_w = tileset->w;
            map->tileset_h = tileset->h;
            int row_length = map->tileset_w / 16; 

            for (int y = 0; y < map->height; ++y) 
            {
                for (int x = 0; x < map->width; ++x) 
                {
                    int tileID = map_layer->data[y * map->width + x] - 1; // Adjusting for 0 index
                    if (tileID >= 0) 
                    {
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
            game->map.texture[0] = largeTexture;
            // Clean up
            SDL_FreeSurface(largeImage);
            SDL_FreeSurface(tileset);
            cute_tiled_free_map(tmap);
        }

        if (strcmp(map_layer->name.ptr, "collision") == 0) {


            game->map.collide = malloc(map->height * sizeof(Tile_t*));
            for(int i = 0; i < map->height; ++i) {
                game->map.collide[i] = malloc(map->width * sizeof(Tile_t));
                memset(game->map.collide[i], 0, map->width * sizeof(Tile_t));
            }

            for (int y = 0; y < map->height; ++y) 
            {
                for (int x = 0; x < map->width; ++x) 
                {
                    //int tileID = map_layer->data[y * map->width + x] - 1; // Adjusting for 0 index
                    int tileID = map_layer->data[y * map->width + x];
                    //printf("tileID=[%d]\n ",tileID);
                    if (tileID == 1711)  // rectangle 
                    {
                        game->map.collide[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
                        game->map.collide[y][x].solid = true;
                    }
                }
            }
        }
    }
}




