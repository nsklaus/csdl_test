#include "core.h"

int main(int argc, char* args[]) {
  SDL_Init(SDL_INIT_VIDEO);
  createWindow();
  createRenderer();
  while(getEvents() != 1 ) {
    update();
  }
  
}
