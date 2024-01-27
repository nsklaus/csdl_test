#include "player.h"
#include <SDL2/SDL_image.h>

const float gravity = 2;

int playerGridY;
int playerGridX;
int playerSpanX;
int playerSpanY;
SDL_Rect area;

//int isJumping = 0;
float jumpTimer = 0.0f;
float jumpDuration = 0.8f;
float jumpStrength = -4.0f;



void player_init(Game_t* game) 
{
  game->player.world_x = 150;           // initial position
  game->player.world_y = 170;

  game->player.srcRect.x = 0;           // cutting in spritesheet
  game->player.srcRect.y = STANDING_F;  // standing sprite (6th row)
  game->player.srcRect.w = TILESIZE;
  game->player.srcRect.h = TILESIZE;

  game->player.dstRect.x = 0;           // screen coords
  game->player.dstRect.y = 0;
  game->player.dstRect.w = TILESIZE;
  game->player.dstRect.h = TILESIZE;

  game->player.frameCount = 1;          // initial animation number of frames
  game->player.currentFrame = 0;

  // Load the player's texture
  game->player.texture = IMG_LoadTexture(game->renderer, "assets/samus.png");
}

void player_update(Game_t* game, float deltaTime) 
{
  // animation
  game->player.currentFrame += 10.0f * deltaTime;  // 10.0f is the speed of the animation
  if (game->player.currentFrame >= game->player.frameCount) {
    game->player.currentFrame -= game->player.frameCount;
  }
  game->player.srcRect.x = (int)game->player.currentFrame * 48;

  // move map according to player position
  if (game->player.world_x > game->width / 2) {
    game->camera.x = game->player.world_x - game->width / 2;
    if (game->camera.x + game->width > game->map.width * 16) {
      game->camera.x = game->map.width * 16 - game->width;
    }
  }
  if (game->player.world_y > game->height / 2) {
    game->camera.y = game->player.world_y - game->height / 2;
    if (game->camera.y + game->height > game->map.height * 16 ) {
      game->camera.y = game->map.height * 16 - game->height;
    }
  }

  // Update world offset based on player position
  game->player.world_x += game->player.dx;
  game->player.world_y += game->player.dy;

  // Update the rendering position
  game->player.dstRect.x = game->player.world_x - game->camera.x;
  game->player.dstRect.y = game->player.world_y - game->camera.y;

  // determine area around player,
  // to limit number of candidates for collision test.
  playerGridX = (game->player.world_x +24 ) / 16;
  playerGridY = (game->player.world_y +24 ) / 16;
  playerSpanX = 64 / 16;
  playerSpanY = 64 / 16;

  if (game->debug)
  {
    // used to display area around player where collision test is possible
    area.x = game->player.world_x +24 - playerSpanX *16 - game->camera.x;
    area.y = game->player.world_y +24 - playerSpanY *16 - game->camera.y;
    area.w = 2* playerSpanX *16;
    area.h = 2* playerSpanY *16;
  }

  move(game, deltaTime);
}

void move(Game_t* game, float deltaTime)
{
  int dx = 2;
  int dy = 2;

  game->player.blocked_jump = false;
  game->player.blocked_up = false;
  game->player.blocked_down = false;
  game->player.blocked_left = false;
  game->player.blocked_right = false;
  game->player.grounded = false;

  game->player.playerRect.x = game->player.dstRect.x + 10;
  game->player.playerRect.y = game->player.dstRect.y;
  game->player.playerRect.w = game->player.dstRect.w - 20;
  game->player.playerRect.h = game->player.dstRect.h;
  game->player.playerRect.x += dx;
  game->player.playerRect.y += dy;

  for (int y = playerGridY - playerSpanY; y <= playerGridY + playerSpanY; y++)
  {
    for (int x = playerGridX - playerSpanX; x <= playerGridX + playerSpanX; x++)
    {
      // ensure we only check for collision within game boundaries
      if ((y >= 0) && (x >= 0) && !(y>game->map.height) && !(x>game->map.width) &&
        (game->map.tile[y][x].rect.x != 0 || game->map.tile[y][x].rect.y != 0))
      {
        if (SDL_HasIntersection(&game->player.playerRect, &game->map.tile[y][x].rect)) {
          // Check for collision with the current tile (game->map.tile[y][x].rect)

          int overlapX = SDL_min(game->player.playerRect.x + game->player.playerRect.w,
                                 game->map.tile[y][x].rect.x + game->map.tile[y][x].rect.w) -
                                 SDL_max(game->player.playerRect.x, game->map.tile[y][x].rect.x);

          int overlapY = SDL_min(game->player.playerRect.y + game->player.playerRect.h,
                                 game->map.tile[y][x].rect.y + game->map.tile[y][x].rect.h) -
                                 SDL_max(game->player.playerRect.y, game->map.tile[y][x].rect.y);

          if (overlapY < overlapX)
          {
            if (game->player.playerRect.y > game->map.tile[y][x].rect.y)
            {
              // Collision on the top side
              game->player.blocked_jump = true;
              game->player.blocked_up = true;
              jumpTimer = 0;
              game->player.jumping = false;
              game->player.playerRect.y = game->map.tile[y][x].rect.y + game->map.tile[y][x].rect.h +1;
              //printf("TOP\n");
            }
            if (game->player.playerRect.y < game->map.tile[y][x].rect.y)
            {
              // Collision on the bottom side
              game->player.grounded = true;
              game->player.blocked_down = true;
              game->player.playerRect.y = game->map.tile[y][x].rect.y - game->player.dstRect.h +1;
              game->player.dstRect.y = game->map.tile[y][x].rect.y - game->player.dstRect.h +1;
            }
          }
          if (overlapY > overlapX )
          {
            if (game->player.playerRect.x > game->map.tile[y][x].rect.x)
            {
              // Collision on the left side
              game->player.blocked_left = true;
              game->player.playerRect.x = game->map.tile[y][x].rect.x + game->map.tile[y][x].rect.w +1;
              //printf("LEFT\n");
            }
            if (game->player.playerRect.x < game->map.tile[y][x].rect.x)
            {
              // Collision on the right side
              game->player.blocked_right = true;
              game->player.playerRect.x = game->map.tile[y][x].rect.x - game->player.playerRect.w +1;
              //printf("RIGHT\n");
            }
          }
        }
      }
    }
  }

  if (game->input.left && !(game->player.blocked_left)) {game->player.world_x -= dx;}
  if (game->input.right && !(game->player.blocked_right)) {game->player.world_x += dx;}

  // prepare for jump
  if (game->input.jump && !(game->player.blocked_jump) && game->player.grounded ) { game->player.jumping = true; }

  // condition for jump ok, initiate jump
  if (game->player.jumping && !(game->player.blocked_jump))
  {
    if(jumpTimer < jumpDuration) { jumpTimer += deltaTime; game->player.world_y -= dy ; }
    if(jumpTimer >= jumpDuration ) { jumpTimer = 0; game->player.jumping = false;}
  }

  // key released, abort jump
  if ((game->input.jump_released)) { jumpTimer = 0; game->player.jumping = false;}

  // apply gravity if there is nothing under player's feet
  if (!game->player.grounded && !(game->player.jumping) && !(game->player.blocked_down))
  {
    game->player.world_y += 1;
  }
}


void player_animation(int frameCount, AnimationType animType, Game_t* game)
{
  game->player.frameCount = frameCount;
  game->player.srcRect.y = animType;
}

void player_render(Game_t* game) 
{
  SDL_RenderCopy(game->renderer, game->player.texture, &game->player.srcRect, &game->player.dstRect);

  if (game->debug)
  {
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); // red
    // SDL_RenderDrawRect(game->renderer, &game->player.dstRect); // player sprite size
    SDL_RenderDrawRect(game->renderer, &game->player.playerRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255); // yellow
    SDL_RenderDrawRect(game->renderer, &area); // render area for collision check
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Reset color
  }
}


void player_destroy(Game_t* game) 
{
  SDL_DestroyTexture(game->player.texture);
  game->player.texture = NULL;
}
