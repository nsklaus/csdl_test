//
//  main.c
//  mygame
//
//  Created by klaus on 24/03/2023.
//

#include <stdio.h>
#include "game.h"
//#include "main.h"


int main(int argc, char* argv[]) {
    Game* game = game_create();
    game_run(game);
    game_destroy(game);
    return 0;
}

