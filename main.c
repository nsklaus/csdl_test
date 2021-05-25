#include "src/core.h"
#include "src/parse_map.h"
#include "src/make_map.h"

int main(int argc, char* args[]) {
  
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  window = SDL_CreateWindow( "hello_sdl2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  font = TTF_OpenFont("assets/roboto.ttf", 24);
  if(!font){printf("Unable to open font");exit(1);}

  struct mymap * map = loadmap("/Users/klaus/Sources/csdl_test/assets/level01.tmx");
  SDL_Surface * map_img = process_map(map);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, map_img);

  while(getEvents() != 1 ) {
    SDL_Rect srcrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_Rect dstrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    render(texture, &srcrect, &dstrect);
    SDL_Delay(20); // 50 fps

    //break;
  }

  SDL_FreeSurface(map_img);
  free_map(map);

  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}

