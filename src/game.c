//
//  game.c
//  mygame
//
//  Created by klaus on 24/03/2023.
//

//#include "main.h"
#include "game.h"
#include "input.h"


Game* game_create() {
    Game* game = malloc(sizeof(Game));
    SDL_Init(SDL_INIT_VIDEO);
    game->window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    //SDL_Texture * texture;
    game->is_running = true;
    fprintf(stderr, "game is running\n" );
    

    
    return game;
}

//SDL_Texture* loapmap(const char* path) {
//    Game* game = get_game();
//    struct mymap * map = loadmap("/Users/klaus/Sources/csdl_test/assets/level01.tmx");
//    SDL_Surface * map_img = process_map(map);
//    SDL_Texture * texture = SDL_CreateTextureFromSurface(game->renderer, map_img);
//    return texture;
//}

void game_run(Game* game) {
    while (game->is_running) {
        
        // Handle input events
        input_handle_events(game);

        // Update game state
        // ...

        // Render graphics
        
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderClear(game->renderer);
        
        // Draw game objects
        SDL_SetRenderDrawColor(game->renderer, 0, 128, 0, 255);
        graphics_draw_rect(game->renderer, 20, 50, 100, 60);
        
        
        SDL_RenderPresent(game->renderer);

        // Pause for a short time to limit the frame rate
        SDL_Delay(16);
    }
}

void game_destroy(Game* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game);
}
