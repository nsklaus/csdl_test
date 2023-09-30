
#include "makemap.h"
#define CUTE_TILED_IMPLEMENTATION
#include "cute_tiled.h"
//LOG("Loading file %s", file);

SDL_Texture* createLargeTexture(SDL_Renderer* renderer) {
    // Load the tileset image
    SDL_Surface* tileset = IMG_Load("Assets/blueMetal.png");
    if (!tileset) {
        fprintf(stderr, "Failed to load tileset: %s\n", IMG_GetError());
        return NULL;
    }

    int tileWidth = 32;
    int tileHeight = 32;
    int rows = 10;
    int cols = 10;

    // Create a large surface to hold the tiles
    SDL_Surface* largeImage = SDL_CreateRGBSurface(0, tileWidth * cols, tileHeight * rows, 32, 0, 0, 0, 0);
    if (!largeImage) {
        fprintf(stderr, "Failed to create large image surface.\n");
        SDL_FreeSurface(tileset);
        return NULL;
    }

    // Fill the large image with tiles from the tileset
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            SDL_Rect srcRect = {x * tileWidth, y * tileHeight, tileWidth, tileHeight};
            SDL_Rect dstRect = {x * tileWidth, y * tileHeight, tileWidth, tileHeight};
            SDL_BlitSurface(tileset, &srcRect, largeImage, &dstRect);
        }
    }

    // Create a texture from the large image
    SDL_Texture* largeTexture = SDL_CreateTextureFromSurface(renderer, largeImage);

    // Clean up
    SDL_FreeSurface(tileset);
    SDL_FreeSurface(largeImage);

    return largeTexture;
}


void process_map(SDL_Renderer* renderer, cute_tiled_map_t* mymap){

  cute_tiled_layer_t* layer = mymap->layers;

  while (layer != NULL)
  {
    fprintf(stderr, "  Layer %d: %s\n", layer->id, layer->name.ptr);
    int num_tiles = layer->width * layer->height;

    if (strcmp(layer->name.ptr, "collision") == 0)
    {
      for (int i = 0; i < num_tiles; i++)
      {
        printf("%d ", layer->data[i]);
      }
      printf("\n");
    }
    layer = layer->next;
  }
}
