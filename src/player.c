//
// Created by Thomas Lienbacher on 03.10.2018.
//

#include <stdio.h>
#include <mem.h>
#include "player.h"

player_t g_player;

void player_init() {
    vec3_set(g_player.pos, 0, 2, 0);
}

void player_control() {
    g_player.yaw += g_control.dmx * g_control.delta * PLAYER_LOOK_SPEED;
    g_player.pitch -= g_control.dmy * g_control.delta * PLAYER_LOOK_SPEED;

    if(g_player.pitch > PLAYER_MAX_PITCH) g_player.pitch = PLAYER_MAX_PITCH;
    if(g_player.pitch < -PLAYER_MAX_PITCH) g_player.pitch = -PLAYER_MAX_PITCH;

    vec3 move = {0};

    move[0] += g_control.kb[SDL_SCANCODE_W];
    move[0] -= g_control.kb[SDL_SCANCODE_S];
    move[2] -= g_control.kb[SDL_SCANCODE_A];
    move[2] += g_control.kb[SDL_SCANCODE_D];

    vec3_norm(move, move);
    float2_rot(move, move+2, g_player.yaw * DEG_2_RAD - FM_PI_2);
    vec3_scale(move, move, PLAYER_SPEED * g_control.delta);

    vec3_add(g_player.pos, g_player.pos, move);
}