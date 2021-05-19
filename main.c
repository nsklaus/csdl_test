#include "src/core.h"
#include "src/parse_map.h"
#include "src/make_map.h"

int main(int argc, char* args[]) {

  SDL_Init(SDL_INIT_VIDEO);
  createWindow();
  createRenderer();
  struct mymap * map = loadmap("assets/level01.tmx");
  //process_map(map);

  //SDL_Surface * image = IMG_Load("assets/bluemetal.png");
  //SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

  while(getEvents() != 1 ) {
    //update(texture);
    process_map(map);
  }
}
