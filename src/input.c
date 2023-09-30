#include "input.h"
#include <stdio.h>

static Input input;

void toggle_fullscreen(Game* game) {  // Added this function
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool isFullscreen = SDL_GetWindowFlags(game->window) & fullscreenFlag;

    SDL_SetWindowFullscreen(game->window, isFullscreen ? 0 : fullscreenFlag);
    SDL_ShowCursor(isFullscreen);
}

void input_handle_events(Game* game) 
{  
    SDL_Event event;
    Camera* camera = &game->camera; // Access the camera from the game structure
    Map* tilemap = &game->tilemap;
    //const int cameraSpeed = 5; // Adjust speed as needed
    
    while (SDL_PollEvent(&event)) {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && game->camera.x > 0) {
            game->camera.x -= camera->speed;
        }
        if (state[SDL_SCANCODE_RIGHT] && game->camera.x < game->tilemap.width * 16 - game->width) {
            game->camera.x += camera->speed;
        }
        if (state[SDL_SCANCODE_UP] && game->camera.y > 0) {
            game->camera.y -= camera->speed;
        }
        if (state[SDL_SCANCODE_DOWN] && game->camera.y < game->tilemap.height * 16 - game->height) {
            game->camera.y += camera->speed;
        }
        switch (event.type) {
            case SDL_QUIT:
                game->is_running = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        input.up = true;
                        if (camera->y > 0) camera->y -= camera->speed;
                        break;
                    case SDLK_s:
                        input.down = true;
                        if (camera->y < tilemap->height - game->height) camera->y += camera->speed;
                        break;
                    case SDLK_a:
                        input.left = true;
                        if (camera->x > 0) camera->x -= camera->speed;
                        break;
                    case SDLK_DOWN:
                        input.right = true;
                        //if (camera->x < tilemap->width - game->width) camera->x += camera->speed;
                        //if (camera->y <= (tilemap->height * 16 - game->height)) { camera->y += camera->speed; }
    // if (game->camera.y + game->camera.height + game->camera.speed <= game->tilemap.height * 16) {
    //     game->camera.y += game->camera.speed;
    // }
    //     if (game->camera.y + game->camera.speed <= (game->tilemap.height * 16 - game->height)) {
    //     game->camera.y += game->camera.speed;
    // }
    // printf("Camera Y before: %d\n", game->camera.y);
    // if (game->camera.y + game->camera.speed <= (game->tilemap.height * 16 - game->height)) {
    //     game->camera.y += game->camera.speed;
    // }
    // printf("Camera Y after: %d\n", game->camera.y);
    // printf("Map height * TILE_SIZE - SCREEN_HEIGHT: %d\n", game->tilemap.height * 16 - game->height);
    // break;
//printf("Camera Y before: %d\n", game->camera.y);
if (game->camera.y + game->camera.speed + game->camera.height < game->tilemap.height * 16) {
    game->camera.y += game->camera.speed;
}
// printf("Camera Y after: %d\n", game->camera.y);
// printf("Map height * TILE_SIZE - SCREEN_HEIGHT: %d\n", game->tilemap.height * 16 - game->height);
// printf("Tilemap Height: %d\n", game->tilemap.height);
// printf("Game Height: %d\n", game->height);


                        break;
                    case SDLK_f:  // Added this case
                        toggle_fullscreen(game); 
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        input.up = false;
                        break;
                    case SDLK_s:
                        input.down = false;
                        break;
                    case SDLK_a:
                        input.left = false;
                        break;
                    case SDLK_d:
                        input.right = false;
                        break;
                }
                break;
        }
    }
    //printf("Camera X: %d, Camera Y: %d\n", game->camera.x, game->camera.y);
}
