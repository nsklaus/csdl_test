#include "core.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;
//SDL_Surface * image;

void createWindow(){ 
    window = SDL_CreateWindow( "hello_sdl2",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
}

void createRenderer(){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

int getEvents(){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitGame();
            return 1;
        }
        switch( event.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        map_x -= 16;
                        break;
                    case SDLK_RIGHT:
                        map_x += 16;
                        break;
                    case SDLK_UP:
                        map_y -= 16;
                        break;
                    case SDLK_DOWN:
                        map_y += 16;
                        break;
                    default:
                        break;
                }
            }
        }
    return 0;
}

void update() {
    SDL_SetRenderDrawColor( renderer, 100, 149, 237, 255);
    SDL_RenderClear( renderer );
    // //render(texture);
    SDL_RenderPresent( renderer );
}

void render(SDL_Texture * texture, SDL_Rect *srcrect, const SDL_Rect *dstrect){
    //SDL_SetRenderDrawColor( renderer, 100, 149, 237, 255);
    SDL_RenderClear( renderer );
    srcrect->x = map_x;
    srcrect->y = map_y;
    //printf("srcrect.x=%d\n",srcrect.x);
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
    SDL_RenderPresent( renderer );
}

void quitGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
