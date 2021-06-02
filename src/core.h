#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

extern SDL_Window *window;
extern SDL_Surface *screenSurface;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern TTF_Font *font;
//int map_x;
//int map_y;

void createFont();
SDL_Renderer *GetRenderer();
int getEvents();
void update();
void render(SDL_Texture * texture, SDL_Rect *srcrect, const SDL_Rect *dstrect);
SDL_Texture *render_font(SDL_Rect *srcrect);
#endif

