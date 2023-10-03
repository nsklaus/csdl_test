#include <SDL_stdinc.h>
#include <stdint.h>
#include <stdio.h>
typedef enum {
    PLAYER_STAND,
    PLAYER_RUN,
    PLAYER_JUMP,
    // Add more states as needed
} PlayerState;

typedef struct {
    int x, y, width, height;
    PlayerState state;
    int frame;
    Uint32 lastFrameTime;
} Player;