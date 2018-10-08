//
// Created by Thomas Lienbacher on 03.10.2018.
//

#ifndef CASTLEGAME3D_PLAYER_H
#define CASTLEGAME3D_PLAYER_H

#include <tengine_math.h>
#include <SDL2/SDL.h>
#include "defs.h"

#define PLAYER_SPEED 2

typedef struct _player_s {
    vec3 pos;
    vec3 vel;
    vec3 lookto;
} player_t;

void player_init(player_t *player);
void player_control(player_t *player, struct control_s *control);

#endif //CASTLEGAME3D_PLAYER_H
