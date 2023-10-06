#include <stdio.h>
#include <unistd.h>
#include "cute_tiled.h"
#include "game.h"
#include "input.h"
#include "player.h"


// time control
Uint32 lastTime = 0;

// create  game instance
Game game;

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

    // make small resolution to adapt an fill fullscreen
    SDL_RenderSetLogicalSize(game.renderer, game.width, game.height);

    // Print the current working directory (can be removed if not needed)
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    }

    // init camera
    game.camera.x = 0;
    game.camera.y = 0;
    game.camera.width = game.width; 
    game.camera.height = game.height; 
    game.camera.speed = 20; 

    game.player = player_init(&game);

    // Load initial map
    load_map("./Assets/level01.json");

    game.quitting = false;
    fprintf(stderr, "game is running\n");
}

// return game instance 
Game* get_game() { return &game; }

// Load the game map and textures
void load_map(const char* path) { largeTexture = createLargeTexture(&game, path); }



// game loop, handling input and rendering
void game_run()
{
    Uint32 lastTime = SDL_GetTicks();  // Initialize lastTime
    float frameTime = 0.0f;

    //Game* game = get_game();
    while ( ! game.quitting)
    {
        // Calculate Delta Time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // in seconds
        lastTime = currentTime;
        frameTime += deltaTime;

        // Handle input events
        input_handle_events(&game);

        player_update(&game, deltaTime);

        // Render game
        render_game();

        // Frame rate control using deltaTime
        if (frameTime < (1.0f / 60.0f))  // 60 FPS 
        {
            SDL_Delay((Uint32)((1.0f / 60.0f - frameTime) * 1000));
        }
        frameTime = 0.0f;  // Reset frameTime for the next iteration
    }
}

/** Render the game elements **/
void render_game()
{
    SDL_RenderClear(game.renderer);

    // camera render rectangle
    SDL_Rect srcRect = { game.camera.x, game.camera.y, game.width, game.height };
    SDL_Rect destRect = { 0, 0, game.width, game.height };

    SDL_RenderCopy(game.renderer, largeTexture, &srcRect, &destRect);
    player_render(&game);
    
    SDL_RenderPresent(game.renderer);
}

// Clean up resources and quits. called automatically from main.c
void game_destroy() 
{
    printf("\n game quits \n");
    player_destroy(&game);
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();  // Clean up SDL initialization
}
