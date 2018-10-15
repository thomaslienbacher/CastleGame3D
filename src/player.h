//
// Created by Thomas Lienbacher on 03.10.2018.
//

#ifndef CASTLEGAME3D_PLAYER_H
#define CASTLEGAME3D_PLAYER_H

#include <tengine_math.h>
#include <SDL2/SDL.h>
#include "defs.h"

#define PLAYER_SPEED 4.0f
#define PLAYER_LOOK_SPEED 1.5f
#define PLAYER_MAX_PITCH 85

typedef struct _player_s {
    vec3 pos;
    vec3 vel;
    float pitch, yaw;
} player_t;

extern player_t player;

void player_init(player_t *player);
void player_control(player_t *player, struct control_s *control);

#endif //CASTLEGAME3D_PLAYER_H
