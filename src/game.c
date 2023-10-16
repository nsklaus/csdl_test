#include <stdio.h>
#include <unistd.h>
#include "cute_tiled.h"
#include "game.h"
#include "input.h"
#include "player.h"


// time control
Uint32 lastTime = 0;

// create  game instance
Game_t game;

// Initialize the game, create window and renderer
void game_create()
{
    game.width = 384;
    game.height= 240;
    SDL_Init(SDL_INIT_VIDEO);

    game.window = SDL_CreateWindow( "Game Title", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game.width, game.height, 
        SDL_WINDOW_OPENGL );
    game.renderer = SDL_CreateRenderer(game.window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(game.renderer, game.width, game.height);

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) { printf("CWD: %s\n", cwd); }

    player_init(&game); 
    map_load("./assets/level01.json"); // Load initial map
    fprintf(stderr, "game starts\n");
}

void map_load(const char* path) 
{
    map_create(&game, path);
    printf("loaded map=[%s] width=[%d], height=[%d] \n", path, game.map.width, game.map.height); 
}

void game_loop()
{

    Uint32 lastTime = SDL_GetTicks();  // Initialize lastTime
    float frameTime = 0.0f;

    while ( ! game.quitting)
    {
        // Calculate Delta Time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // in seconds
        lastTime = currentTime;
        frameTime += deltaTime;

        input_update(&game);
        map_update(&game);
        player_update(&game, deltaTime);
        game_render();

        // Frame rate control using deltaTime
        if (frameTime < (1.0f / 60.0f))  // 60 FPS 
        {
            SDL_Delay((Uint32)((1.0f / 60.0f - frameTime) * 1000));
        }
        frameTime = 0.0f;  // Reset frameTime for the next iteration
    }
}

void game_render()
{
    //SDL_RenderClear(game.renderer);
    map_render(&game);
    player_render(&game);
    SDL_RenderPresent(game.renderer);
}

void game_destroy() 
{
    printf("game ends \n");
    player_destroy(&game);
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();
}
