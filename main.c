#include "src/core.h"
#include "src/map.h"

int main(int argc, char* args[]) {

  SDL_Init(SDL_INIT_VIDEO);
  createWindow();
  createRenderer();
  loadmap();

  while(getEvents() != 1 ) {
    update();
  }
}
