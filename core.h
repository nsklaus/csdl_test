#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window *window;
extern SDL_Surface *screenSurface;
extern SDL_Renderer *renderer;
extern SDL_Event event;

bool init();
SDL_Window* getWindow();
SDL_Renderer* getRenderer();
void getEvents();
void update();
void quitGame();
#endif