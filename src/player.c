//
// Created by Thomas Lienbacher on 03.10.2018.
//

#include <stdio.h>
#include <mem.h>
#include <light.h>
#include "player.h"
#include "world.h"
#include "engine.h"

player_t g_player;

void player_init() {
    vec3_set(g_player.body.pos, 0, 1, 0);
    g_player.inair = 1;
    g_player.body.height = PLAYER_HEIGHT;
    g_player.body.radius = PLAYER_RADIUS;
    g_player.lightId = lightengine_get_id(g_lightengine);
    g_physicsengine.player = &g_player.body;
}

void player_control() {
    lightengine_set(g_lightengine, g_player.lightId, (vec3) {1.0f, 1.0f, 1.0f},
                    (vec3) {g_player.body.pos[0], g_player.body.pos[1] + PLAYER_HEIGHT, g_player.body.pos[2]}, 3.5f);

    g_player.yaw += g_control.dmx * g_control.delta * PLAYER_LOOK_SPEED;
    g_player.pitch -= g_control.dmy * g_control.delta * PLAYER_LOOK_SPEED;

    if (g_player.pitch > PLAYER_MAX_PITCH) g_player.pitch = PLAYER_MAX_PITCH;
    if (g_player.pitch < -PLAYER_MAX_PITCH) g_player.pitch = -PLAYER_MAX_PITCH;

    vec2 move = {0};

    move[0] += g_control.kb[SDL_SCANCODE_W];
    move[0] -= g_control.kb[SDL_SCANCODE_S];
    move[1] -= g_control.kb[SDL_SCANCODE_A];
    move[1] += g_control.kb[SDL_SCANCODE_D];


    if (g_control.kb[SDL_SCANCODE_SPACE] && !g_player.inair) {
        g_player.body.vel[1] = JUMP_STRENGTH;
        g_player.inair = 1;
    }

    vec2_norm(move, move);
    vec2_rot(move, move, g_player.yaw * DEG_2_RAD - FM_PI_2);
    vec2_scale(move, move, PLAYER_SPEED);

    g_player.body.vel[0] = move[0];
    g_player.body.vel[2] = move[1];
}