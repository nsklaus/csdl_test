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
    game.width = 384;
    game.height= 240;
    SDL_Init(SDL_INIT_VIDEO);

    game.window = SDL_CreateWindow( "Game Title", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game.width, game.height, 
        SDL_WINDOW_OPENGL );

    game.renderer = SDL_CreateRenderer(game.window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
    game.camera.speed = 5; 

    // Load initial map
    load_map("./Assets/level01.json");

    game.quitting = false;
    fprintf(stderr, "game is running\n");
}

/** return game instance **/
Game* get_game() { return &game; }

/** Load the game map and textures **/
void load_map(const char* path) { largeTexture = createLargeTexture(&game, path); }

/** Render the game elements **/
void render_game()
{
    SDL_RenderClear(game.renderer);

int srcWidth = game.width;
int srcHeight = game.height;

if(game.camera.x + srcWidth > game.tilemap.width * 16) {
    srcWidth = (game.tilemap.width * 16) - game.camera.x;
    printf("stuff111\n");
}

if(game.camera.y + srcHeight > game.tilemap.height * 16) {
    srcHeight = (game.tilemap.height * 16) - game.camera.y;
    printf("stuff222\n");
}
    // camera render rectangle
    SDL_Rect srcRect = { game.camera.x, game.camera.y, game.width, game.height };

    SDL_Rect destRect = { 0, 0, game.width, game.height };
    
    if (game.input.down || game.input.up || game.input.down || game.input.right)
    {
// debug
printf("srcRect: x=%d, y=%d, w=%d, h=%d\n", srcRect.x, srcRect.y, srcRect.w, srcRect.h);
printf("destRect: x=%d, y=%d, w=%d, h=%d\n", destRect.x, destRect.y, destRect.w, destRect.h);
    }    
    

    SDL_RenderCopy(game.renderer, largeTexture, &srcRect, &destRect);
    SDL_RenderPresent(game.renderer);
}

// game loop, handling input and rendering
void game_run()
{
    //Game* game = get_game();
    while ( ! game.quitting)
    {
        //take the time
        frameStart = SDL_GetTicks();

        // Handle input events
        input_handle_events(&game);

        // Render game
        render_game();

        // calculate how long it took since we started timer.
        // if frameDelay is bigger than frameTime wait a bit
        // to reach desired target FPS.
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }
    }
}

// Clean up resources and quits. called automatically from main.c
void game_destroy() 
{
    printf("\n game quits \n");
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();  // Clean up SDL initialization
}
