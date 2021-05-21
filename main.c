#include "src/core.h"
#include "src/parse_map.h"
#include "src/make_map.h"

int main(int argc, char* args[]) {

  SDL_Init(SDL_INIT_VIDEO);
  createWindow();
  createRenderer();
  struct mymap * map = loadmap("assets/level01.tmx");
  //process_map(map);

  while(getEvents() != 1 ) {
    //update();  //app work fine
    process_map(map); // app gets unresponsive
  }
}
