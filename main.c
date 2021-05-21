#include "src/core.h"
#include "src/parse_map.h"
#include "src/make_map.h"

int main(int argc, char* args[]) {

  SDL_Init(SDL_INIT_VIDEO);
  createWindow();
  createRenderer();
  struct mymap * map = loadmap("assets/level01.tmx");
  SDL_Surface * map_img = process_map(map);

  //process_map(map);

  while(getEvents() != 1 ) {
    //update();  //app work fine
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, map_img);
    SDL_Rect srcrect = {0,0,320,240};
    SDL_Rect dstrect = {0,0,320,240};
    render(texture, &srcrect, &dstrect);
    SDL_Delay(20); // 50 fps
  }
}
