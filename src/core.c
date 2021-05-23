#include "core.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;
TTF_Font* font;
int texW, texH = 0;
//SDL_Surface * image;
int map_x;
int map_y;


int getEvents(){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
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
    SDL_RenderClear( renderer );

    //limit map offset
    if (map_x < 0) map_x = 0;
    if (map_x > 640) map_x = 640; //960;
    if (map_y < 0) map_y = 0;
    if (map_y > 160) map_y = 160; //400;

    srcrect->x = map_x;
    srcrect->y = map_y;

    SDL_RenderCopy(renderer, texture, srcrect, dstrect);


//    SDL_QueryTexture(render_font(srcrect), NULL, NULL, &texW, &texH);
//    SDL_Rect dstrectX = { 0, 0, texW, texH };
//    SDL_RenderCopy(renderer, render_font(srcrect), NULL, &dstrectX);

    SDL_RenderPresent( renderer );
}

SDL_Texture *render_font(SDL_Rect *srcrect){
    SDL_Color color = { 255, 255, 255 };


    //map offset XY value
    int x = srcrect->x;
    int y = srcrect->y;
    char *p, castx[5], casty[5], final[32];
    char *prefix1 = "mapx=";
    char *prefix2 = "  mapy=";
    sprintf(castx,"%d",x);
    sprintf(casty,"%d",y);
    snprintf(final, sizeof(final), "%s%s%s%s", prefix1, castx, prefix2, casty);
    p = final;

    SDL_Surface * surface = TTF_RenderText_Solid(font, p, color);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, surface);
    return tex;
}

