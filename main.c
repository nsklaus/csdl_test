#include "core.h"

int main(int argc, char* args[]) {
  SDL_Init(SDL_INIT_VIDEO);
  getWindow();
  getRenderer();
  while(true) {
    getEvents();
    update();
  }
}
