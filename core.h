#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window *window;
extern SDL_Surface *screenSurface;
extern SDL_Renderer *renderer;
extern SDL_Event event;

bool init();
void createWindow();
void createRenderer();
void getEvents();
void update();
void quitGame();
#endif