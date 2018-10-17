//
// Created by Thomas Lienbacher on 03.10.2018.
//

#ifndef CASTLEGAME3D_PLAYER_H
#define CASTLEGAME3D_PLAYER_H

#include <tengine_math.h>
#include <SDL2/SDL.h>
#include "defs.h"

#define PLAYER_SPEED 8.0f
#define PLAYER_LOOK_SPEED 1.5f
#define PLAYER_MAX_PITCH 85.0f
#define PLAYER_RADIUS 1.0f
#define GRAVITY -4.0f
#define PLAYER_HEIGHT 2.0f
#define JUMP_STRENGTH 1.8f

typedef struct _player_s {
    vec3 pos;
    float yvel;
    char inair;
    float pitch, yaw;
} player_t;

extern player_t g_player;

void player_init();
void player_control();

#endif //CASTLEGAME3D_PLAYER_H
