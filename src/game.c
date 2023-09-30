#include "cute_tiled.h"
#include "game.h"
#include "input.h"
#include <stdio.h>
#include <unistd.h>

static Game game;

// Initialize the game, create window and renderer
void game_create()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    game.window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, 
                                   SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
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

    // Load initial map
    load_map("./Assets/level01.json");

    game.is_running = true;
    fprintf(stderr, "game is running\n");
}

Game* get_game(void) { return &game; }

// Load the game map and textures
void load_map(const char* path)
{
    largeTexture = createLargeTexture(game.renderer);
}

// Render the game elements
void render_game()
{
    if (largeTexture) {
        SDL_RenderCopy(game.renderer, largeTexture, NULL, NULL);
        SDL_RenderPresent(game.renderer);
    } else {
        fprintf(stderr, "Failed to create large texture.\n");
    }
}

// The main game loop, handling input and rendering
void game_run()
{
    Game* game = get_game();
    while (game->is_running)
    {
        // Handle input events
        input_handle_events(game);

        // Render game
        render_game();

        SDL_Delay(16);
    }
}

// Clean up resources and close the game
void game_destroy() 
{
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();  // Clean up SDL initialization
}
