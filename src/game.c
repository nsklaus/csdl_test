#include "cute_tiled.h"
#include "game.h"
#include "input.h"
#include <stdio.h>
#include <unistd.h>

// stuff needed to time gameloop
const int FPS = 60;  // Set target FPS
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

// create  game instance
Game game;


// Initialize the game, create window and renderer
void game_create()
{
    game.width = 800;
    game.height= 600;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    //game.window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    game.window = SDL_CreateWindow( "Game Title", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game.width, game.height, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    if (!game.window) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return;
    }

    game.renderer = SDL_CreateRenderer(game.window, -1, 
                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!game.renderer) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        return;
    }

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
    game.camera.speed = 5; 

    // Load initial map
    load_map("./Assets/level01.json");

    game.is_running = true;
    fprintf(stderr, "game is running\n");
}

Game* get_game(void) { return &game; }

// Load the game map and textures
void load_map(const char* path)
{
    largeTexture = createLargeTexture(&game, path);
}

// Render the game elements
void render_game()
{

    SDL_RenderClear(game.renderer);
    // SDL_Rect srcRect = {
    //     game.camera.x, game.camera.y,
    //     game.width, game.height
    // };

    // SDL_Rect destRect = {
    //     0, 0, game.width, game.height
    // };
    //     // Adjust srcRect to ensure it does not exceed the large texture's dimensions
    // if (srcRect.x + srcRect.w > game.tilemap.width * 16) {
    //     srcRect.w = game.tilemap.width * 16 - srcRect.x;
    // }
    // if (srcRect.y + srcRect.h > game.tilemap.height * 16) {
    //     srcRect.h = game.tilemap.height * 16 - srcRect.y;
    // }
    SDL_Rect destRect = {
        0, 0,
        game.tilemap.width * 16, game.tilemap.height * 16
    };


    SDL_Rect cameraRect = {
        game.camera.x, game.camera.y,
        game.width, game.height
    };

    //SDL_RenderCopy(game.renderer, largeTexture, NULL, &destRect);
    if (largeTexture) 
    {
        SDL_RenderCopy(game.renderer, largeTexture, &cameraRect, &destRect);

        //SDL_RenderCopy(game.renderer, largeTexture, &srcRect, &destRect);
        //SDL_RenderCopy(game.renderer, largeTexture, NULL, NULL);
        SDL_RenderPresent(game.renderer);
    } else {
        fprintf(stderr, "Failed to create large texture.\n");
    }
    //printf("Dest Rect X: %d, Y: %d, Width: %d, Height: %d\n", destRect.x, destRect.y, destRect.w, destRect.h);
//printf("Dest Rect Height: %d\n", destRect.h);
//printf("Dest Rect Y: %d\n", destRect.y);
//printf("Source Rect X: %d, Y: %d, Width: %d, Height: %d\n", srcRect.x, srcRect.y, srcRect.w, srcRect.h);

}

// game loop, handling input and rendering
void game_run()
{
    Game* game = get_game();
    while (game->is_running)
    {
        //take the time
        frameStart = SDL_GetTicks();

        // Handle input events
        input_handle_events(game);

        // Render game
        render_game();

        // calculate how long it took since we started timer.
        // if frameDelay is bigger than frameTime wait a bit
        // to reach desired target FPS.
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }
    }
}

// Clean up resources and close the game
void game_destroy() 
{
    printf("\ngame quits \n");
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();  // Clean up SDL initialization
}
