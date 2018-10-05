//
// Created by Thomas Lienbacher on 03.10.2018.
//

#include "player.h"

void player_init(player_t *player) {
    vec3_set(player->pos, 0, 1, 0);
    vec3_cpy(player->vel, VEC3_ZERO);
    vec3_set(player->lookat, 0, 0, -1);
}

//TODO: optimize code, set player speed var
void player_control(player_t *player, struct control_s *control) {
    //TODO: replace with new tengine functions
    static float la = 0;
    la += control->kb[SDL_SCANCODE_E] * control->delta * M_2_PI;
    la -= control->kb[SDL_SCANCODE_Q] * control->delta * M_2_PI;

    player->lookat[0] = cosf(la);
    player->lookat[2] = sinf(la);

    float ang = atan2f(player->lookat[2], player->lookat[0]);

    vec3 move = {0};

    move[0] += control->kb[SDL_SCANCODE_W];
    move[0] -= control->kb[SDL_SCANCODE_S];

    move[2] += control->kb[SDL_SCANCODE_A];
    move[2] -= control->kb[SDL_SCANCODE_D];

    //TODO: replace with new tengine functions
    float len = vec3_len(move);
    if(len > 0) vec3_norm(move, move); // TODO: fix this bug where it crashes because len == 0

    vec3 nmove;
    nmove[0] = (cosf(la) * move[0] - sinf(la) * move[2]) * control->delta;
    nmove[2] = (sinf(la) * move[0] + cosf(la) * move[2]) * control->delta;

    vec3_add(player->pos, player->pos, nmove);
}