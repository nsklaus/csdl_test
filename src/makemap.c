
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define CUTE_TILED_IMPLEMENTATION
#include "cute_tiled.h"
#include "game.h"

void map_create(Game_t* game, const char* path) 
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
      char buffer[512];
      sprintf(buffer, "assets/%s", tmap->tilesets->image.ptr);

      SDL_Surface* tileset = IMG_Load(buffer);
      if(!tileset) { fprintf(stderr, "failed to load tileset %s\n", buffer); exit(1); }

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
      //cute_tiled_free_map(tmap);
    }

    if (strcmp(map_layer->name.ptr, "collision") == 0)
    {
      game->map.tile = malloc(map->height * sizeof(Tile_t*));
      for(int i = 0; i < map->height; ++i)
      {
        game->map.tile[i] = malloc(map->width * sizeof(Tile_t));
        memset(game->map.tile[i], 0, map->width * sizeof(Tile_t));
      }

      for (int y = 0; y < map->height; ++y)
      {
        for (int x = 0; x < map->width; ++x)
        {
          int tileID = map_layer->data[y * map->width + x];

          if (tileID == 1711 )  // rectangle
          {
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }

          if (tileID == 1705 )  // triangle
          {
            //printf("x=[%d] y=[%d]\n",x,y);
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }

          if (tileID == 1706 )  // triangle
          {
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }
          if (tileID == 1707 )  // triangle
          {
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }
          if (tileID == 1708 )  // triangle
          {
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }
          if (tileID == 1721 )  // triangle
          {
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }
          if (tileID == 1722 )  // triangle
          {
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }
          if (tileID == 1723 )  // triangle
          {
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }
          if (tileID == 1724 )  // triangle
          {
            game->map.tile[y][x].rect = (SDL_Rect){x*16, y*16, 16, 16};
            game->map.tile[y][x].solid = true;
          }
        }
      }
    }
  }
  cute_tiled_free_map(tmap);
}

void map_update(Game_t* game)
{
  // Update collision rectangles positions (scroll along map)
  for (int y = 0; y < game->map.height; ++y)
  {
    for (int x = 0; x < game->map.width; ++x)
    {
      if (game->map.tile[y][x].solid)
      {
        game->map.tile[y][x].rect.x = (x * 16) - game->camera.x;
        game->map.tile[y][x].rect.y = (y * 16) - game->camera.y;
      }
    }
  }
  // camera render rectangle
  game->camera.srcRect = (SDL_Rect){ game->camera.x, game->camera.y, game->width, game->height };
  game->camera.dstRect = (SDL_Rect){ 0, 0, game->width, game->height };
}

void map_render(Game_t* game)
{
  SDL_RenderCopy(game->renderer, game->map.texture[0], &game->camera.srcRect, &game->camera.dstRect);

  // DEBUG: render collision rectangles
  if (game->debug)
  {
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); // Set color to red for debugging

    for (int y = 0; y < game->map.height; ++y)
    {
      for (int x = 0; x < game->map.width; ++x)
      {
        if (game->map.tile[y][x].solid)
        {
          SDL_RenderDrawRect(game->renderer, &game->map.tile[y][x].rect);
        }
      }
    }
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Reset color
  }
}



