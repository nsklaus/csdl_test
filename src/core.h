#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Window *window;
extern SDL_Surface *screenSurface;
extern SDL_Renderer *renderer;
extern SDL_Event event;

void createWindow();
void createRenderer();
SDL_Renderer *SDL_GetRenderer();
int getEvents();
void update();
void render(SDL_Texture * texture);
void quitGame();
#endif