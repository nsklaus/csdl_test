
//#include "main.h"
#include "game.h"
#include "input.h"
#define CUTE_TILED_H_IMPLEMENTATION
#include "cute_tiled.h"
#include <stdio.h>
#include <unistd.h>

static Game game;

void game_create()
{
  SDL_Init(SDL_INIT_VIDEO);
  game.window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
  game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working directory: %s\n", cwd);
  }
  // load initial map
  load_map("./Assets/level01.json");
  game.is_running = true;
  fprintf(stderr, "game is running\n" );
}

Game* get_game(void)
{
  return &game;
}

//SDL_Texture*
void load_map(const char* path)
{
  cute_tiled_map_t* mymap;
  mymap = cute_tiled_load_map_from_file(path, NULL);

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


  //Game* game = get_game();
  //cute_tiled_map_t* mymap;
  //mymap = cute_tiled_load_map_from_file(path, NULL);
  //fprintf(stderr, "map width = %d \n", mymap->width);
  //struct mymap * map = process_map(<#struct mymap *map#>)("/Users/klaus/Sources/csdl_test/assets/level01.tmx");
  //SDL_Surface * map_img = process_map(map);
  //SDL_Texture * texture = SDL_CreateTextureFromSurface(game->renderer, map_img);
  //SDL_Texture * texture;
  //return texture;
}

void game_run()
{
  Game* game = get_game();
  while (game->is_running)
  {
    // Handle input events
    input_handle_events(game);

    // Update game state
    // ...

    // Render graphics

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    // Draw game objects
    SDL_SetRenderDrawColor(game->renderer, 0, 128, 0, 255);
    graphics_draw_rect(game->renderer, 20, 50, 100, 60);


    SDL_RenderPresent(game->renderer);
    // Pause for a short time to limit the frame rate
    SDL_Delay(16);
  }
}

void game_destroy() {
  Game* game = get_game();
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  //free(game);
}
