#include "src/core.h"
#include "src/parse_map.h"

int main(int argc, char* args[]) {

  SDL_Init(SDL_INIT_VIDEO);
  createWindow();
  createRenderer();
  loadmap("assets/level01.tmx");

  while(getEvents() != 1 ) {
    update();
  }
}
