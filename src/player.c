//
// Created by Thomas Lienbacher on 03.10.2018.
//

#include <stdio.h>
#include <mem.h>
#include "player.h"

void player_init(player_t *player) {
    memset(player, 0, sizeof(player_t));
    vec3_set(player->pos, 0, 1, 0);
}

void player_control(player_t *player, struct control_s *control) {
    player->yaw += control->dmx * control->delta * PLAYER_LOOK_SPEED;
    player->pitch -= control->dmy * control->delta * PLAYER_LOOK_SPEED;

    if(player->pitch > 80) player->pitch = 80;
    if(player->pitch < -80) player->pitch = -80;

    vec3 move = {0};

    move[0] += control->kb[SDL_SCANCODE_W];
    move[0] -= control->kb[SDL_SCANCODE_S];
    move[2] -= control->kb[SDL_SCANCODE_A];
    move[2] += control->kb[SDL_SCANCODE_D];

    vec3_norm(move, move);
    float2_rot(move, move+2, player->yaw * DEG_2_RAD - M_PI_2);//TODO: replace with tengine pi constant
    vec3_scale(move, move, PLAYER_SPEED * control->delta);

    vec3_add(player->pos, player->pos, move);
}