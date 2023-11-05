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
float jumpDuration = 1.0f;
//float jumpStrength = -2.0f;


void player_init(Game_t* game) 
{
  game->player.world_x = 150;           // initial position
  game->player.world_y = 176;

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
  game->player.grounded = true;
  game->player.jump_release = true;
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

  /*
  // wip: player additional collision rectangles
  game->player.headRect.x = game->player.dstRect.x + 14;
  game->player.headRect.y = game->player.dstRect.y - 5;
  game->player.headRect.w = game->player.dstRect.w - 26;
  game->player.headRect.h = 5;
*/

  game->player.feetRect.x = game->player.dstRect.x + 14;
  game->player.feetRect.y = game->player.dstRect.y + game->player.dstRect.h;
  game->player.feetRect.w = game->player.dstRect.w - 26;
  game->player.feetRect.h = 5;
/*
  game->player.leftRect.x = game->player.dstRect.x ;
  game->player.leftRect.y = game->player.dstRect.y ;
  game->player.leftRect.w = 5;
  game->player.leftRect.h = game->player.dstRect.h;

  game->player.rightRect.x = game->player.dstRect.x + game->player.dstRect.w;
  game->player.rightRect.y = game->player.dstRect.y;
  game->player.rightRect.w = 5;
  game->player.rightRect.h = game->player.dstRect.h;
  */

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

  if (game->player.jump && game->player.jumping)
  {
    if (jumpTimer < jumpDuration) { jumpTimer += deltaTime; }
    if (jumpTimer >= jumpDuration) {
      game->player.jumping = false;
      game->player.jump= false;
      jumpTimer = 0;}
  }

  apply_gravity(game);
}

void apply_gravity(Game_t* game)
{
  grounded(game);
  if (!game->player.grounded && !(game->player.jumping))
  {
    game->player.world_y += gravity;
  }
}

void grounded(Game_t* game)
{
  for (int y = playerGridY - playerSpanY; y <= playerGridY + playerSpanY; y++)
  {
    for (int x = playerGridX - playerSpanX; x <= playerGridX + playerSpanX; x++)
    {
      if ((y >= 0) && (x >= 0) && y <= game->map.height && x <= game->map.width &&
        (game->map.tile[y][x].rect.x != 0 || game->map.tile[y][x].rect.y != 0))
      {
        if (SDL_HasIntersection(&game->player.feetRect,&game->map.tile[y][x].rect))
        {
          game->player.dstRect.y = game->map.tile[y][x].rect.y - game->player.dstRect.w;
          game->player.grounded = true;
          return;
        }
        //printf("playerGridX=[%d] playerGridY=[%d] playerSpanX=[%d] playerSpanY=[%d]\n",
        //playerGridX,playerGridY,playerSpanX,playerSpanY);
        //printf("x=[%d]  y=[%d]\n",x,y);
      }
    }
  }
  game->player.grounded = false;
}

void move(Game_t* game, int dx, int dy) 
{

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

          //printf("overlapX=[%d] overlapY=[%d]\n",overlapX, overlapY);
          //printf("playerRect.y=[%d] tile[y][x].rect.y=[%d]\n\n", game->player.playerRect.y,
          //                       game->map.tile[y][x].rect.y);
          if (overlapY < overlapX)
          {
            if (game->player.playerRect.y > game->map.tile[y][x].rect.y)
            {
              // Collision on the top side
              game->player.jump = false;
              game->player.jumping = false;
              game->player.jump_release = false;
              game->player.playerRect.y = game->map.tile[y][x].rect.y + game->map.tile[y][x].rect.h;
              printf("set game->player.up to false\n");
              break;
            }
            if (game->player.playerRect.y < game->map.tile[y][x].rect.y)
            {
              // Collision on the bottom side
              //game->player.down = false;
              game->player.grounded = true;
              game->player.playerRect.y = game->map.tile[y][x].rect.y - game->player.dstRect.h;
              printf("set game->player.down to false\n");
              break;
            }
          }

          if (overlapY > overlapX )
          {
            // printf("playerRect.x=[%d] tile[y][x].rect.x=[%d]\n",
            // game->player.playerRect.x,  game->map.tile[y][x].rect.x);
            if (game->player.playerRect.x > game->map.tile[y][x].rect.x)
            {
              // Collision on the left side
              game->player.left = false;
              game->player.playerRect.x = game->map.tile[y][x].rect.x + game->map.tile[y][x].rect.w;
              printf("set game->player.left to false\n");
              break;
            }
            if (game->player.playerRect.x < game->map.tile[y][x].rect.x)
            {
              // Collision on the right side
              game->player.right = false;
              game->player.playerRect.x = game->map.tile[y][x].rect.x - game->player.playerRect.w;
              printf("set game->player.right to false\n");
              break;
            }
          }
        }
      }
    }
  }
  //printf("game->player.right=[%s]\n",game->player.right ? "true" : "false");
  if (game->player.jump && game->player.grounded && game->player.jump_release)
  {
    printf("init jump \n");
    game->player.jumping = true;
  }

  if (game->player.jumping)
  {
    printf("jumping \n");
    if(jumpTimer >= jumpDuration) { game->player.jump_release = false; printf("\n\n BLEEEEEH\n\n");}
    if(jumpTimer < jumpDuration) { game->player.world_y += dy; }
    //if(jumpTimer >= jumpDuration) { game->player.jump_release = false; }
  }

  if (game->player.down) {game->player.world_y += dy;}
  if (game->player.left) {game->player.world_x += dx;}
  if (game->player.right) {game->player.world_x += dx;}

  game->player.blocked = false;
  printf("grounded=[%s]\n",game->player.grounded ? "true" : "false");


  /*
   *  // Vertical Collision Detection
   *  i *f (dy > 0) {
   *  // Player is moving down
   *  // Check for collisions in the downward direction only
   *  // Adjust the player's vertical position accordingly
   *  // ...
} else if (dy < 0) {
  // Player is moving up
  // Check for collisions in the upward direction only
  // Adjust the player's vertical position accordingly
  // ...
}


if (playerIsOnGround && userPressesJumpKey && !isJumping) {
  isJumping = 1;
  jumpTimer = 0.0f;  // Reset the jump timer
}

if (isJumping) {
  player_update(&game, deltaTime); // Pass deltaTime to player update
  jumpTimer += deltaTime;  // Update the jump timer
  if (jumpTimer >= jumpDuration) {
    isJumping = 0;  // The jump duration has passed, stop jumping
}
}


*/
}




// how much frames for a given anim type
void player_animation(int frameCount, AnimationType animType, Game_t* game)
{
  game->player.frameCount = frameCount;
  game->player.srcRect.y = animType;
}

void player_render(Game_t* game) 
{
  SDL_RenderCopy(game->renderer, game->player.texture, &game->player.srcRect, &game->player.dstRect);


  if (!game->player.blocked)
  {
    if (game->player.jump && game->player.jump_release)  { move( game,  0, -2); }
    if (game->player.down)  { move( game,  0,  2); }
    if (game->player.left)  { move( game, -2,  0); }
    if (game->player.right) { move( game,  2,  0); }
  }

  if (game->debug)
  {
    // area.x = game->player.world_x +24 - playerSpanX *16 - game->camera.x;
    // area.y = game->player.world_y +24 - playerSpanY *16 - game->camera.y;
    // area.w = 2* playerSpanX *16;
    // area.h = 2* playerSpanY *16;

    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); // red
    // SDL_RenderDrawRect(game->renderer, &game->player.headRect);
    // SDL_RenderDrawRect(game->renderer, &game->player.feetRect);
    // SDL_RenderDrawRect(game->renderer, &game->player.leftRect);
    // SDL_RenderDrawRect(game->renderer, &game->player.rightRect);
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
