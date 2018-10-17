//
// Created by Thomas Lienbacher on 03.10.2018.
//

#include <stdio.h>
#include <mem.h>
#include "player.h"
#include "world.h"

player_t g_player;

void player_init() {
    vec3_set(g_player.pos, 0, PLAYER_HEIGHT, 0);
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


    if(g_control.kb[SDL_SCANCODE_SPACE] && !g_player.inair) {
        g_player.yvel = JUMP_STRENGTH;
        g_player.inair = 1;
    }

    g_player.yvel += GRAVITY * g_control.delta;

    vec3_norm(move, move);
    float2_rot(move, move+2, g_player.yaw * DEG_2_RAD - FM_PI_2);
    move[1] += g_player.yvel;
    vec3_scale(move, move, PLAYER_SPEED * g_control.delta);

    vec3_add(g_player.pos, g_player.pos, move);
    if(g_player.pos[1] < PLAYER_HEIGHT) g_player.inair = 0;

    g_player.pos[0] = clampf(g_player.pos[0], -WORLD_SIZE + PLAYER_RADIUS, WORLD_SIZE - PLAYER_RADIUS);
    g_player.pos[1] = clampf(g_player.pos[1], PLAYER_HEIGHT, 2000.0f);
    g_player.pos[2] = clampf(g_player.pos[2], -WORLD_SIZE + PLAYER_RADIUS, WORLD_SIZE - PLAYER_RADIUS);
}