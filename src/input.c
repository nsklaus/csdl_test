#include "input.h"
#include <SDL2/SDL_scancode.h>
#include <stdio.h>
#include "player.h"

const float jumpStrength = -5.0f;

void toggle_fullscreen(Game_t* game) 
{
  Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
  bool isFullscreen = SDL_GetWindowFlags(game->window) & fullscreenFlag;
  SDL_SetWindowFullscreen(game->window, isFullscreen ? 0 : fullscreenFlag);
  SDL_ShowCursor(isFullscreen);
}

void input_update(Game_t* game) 
{
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0)
  {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (event.type == SDL_QUIT)
    {
      game->quitting = true;
    }

    if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_d:
          if (event.key.repeat == 0)
          {
            game->debug = !game->debug;
          }
          break;

        case SDLK_f:
          game->fullscreen = true;
          toggle_fullscreen(game);
          break;

        case SDLK_ESCAPE:
          game->quitting = true;
          break;
      }
    }
    if (event.type == SDL_KEYUP)
    {
      if (game->player.srcRect.y != STANDING_F ) { player_animation(1, STANDING_F, game); }
      game->player.up = false;
      game->player.down = false;
      game->player.left = false;
      game->player.right = false;
      game->player.jump = false;
      game->player.blocked = false;
      game->player.dx = 0;
      game->player.dy = 0;
    }

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
      if (game->player.srcRect.y != RUNNING_L ) { player_animation(9, RUNNING_L, game); }
      game->player.left = true;
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
      if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
      game->player.right = true;
    }

    if (currentKeyStates[SDL_SCANCODE_UP])
    {
      if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
      game->player.up = true;
    }

    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
      if (game->player.srcRect.y != RUNNING_R ) { player_animation(9, RUNNING_R, game); }
      game->player.down = true;
    }

    if (currentKeyStates[SDL_SCANCODE_SPACE])
    {
      //if (game->player.grounded) { game->player.vy = jumpStrength; }
      if (game->player.srcRect.y != JUMPING_R ) { player_animation(7, JUMPING_R, game); }
      game->player.jump = true;
    }
  }
}
