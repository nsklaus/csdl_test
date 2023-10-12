
#include "game.h"

//int main(int argc, char* argv[]) {
int main(void) 
{
  game_create();
  game_loop();
  game_destroy();
  return 0;
}


