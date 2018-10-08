//
// Created by Thomas Lienbacher on 03.10.2018.
//

#include <stdio.h>
#include "player.h"

void player_init(player_t *player) {
    vec3_set(player->pos, 0, 1, 0);
    vec3_cpy(player->vel, VEC3_ZERO);
    vec3_set(player->lookto, 0, 0, -1);
}

void player_control(player_t *player, struct control_s *control) {

    vec3_norm(player->lookto, player->lookto);
    float pitch = asinf(-player->lookto[1]);
    float yaw = atan2f(player->lookto[2], player->lookto[0]);

    yaw += control->dmx * control->delta * 0.05f;
    pitch += c

    printf("%f %f\n", yaw * RAD_2_DEG, pitch * RAD_2_DEG);

    player->lookto[0] = cosf(yaw);
    player->lookto[1] = pitch;
    player->lookto[2] = sinf(yaw);

    /*float len = vec3_len(player->lookto);
    float yaw = atan2f(player->lookto[2], player->lookto[0]);
    float vertAng = acosf(player->lookto[2] / len);

    yaw += control->dmx * control->delta * 0.05f;
    vertAng += control->dmy * control->delta * 0.05f;

    printf("h: %f v: %f\n", yaw * RAD_2_DEG, vertAng * RAD_2_DEG);

    player->lookto[0] = cosf(yaw);
    player->lookto[1] = sinf(yaw) * cosf(vertAng);
    player->lookto[2] = sinf(yaw);*/

    //player->lookto[0] = cosf(yaw) * sinf(vertAng);
    //player->lookto[1] = sinf(yaw) * sinf(vertAng);
    //player->lookto[2] = -cosf(vertAng);

    //centerX = cos(rotationAngle) * sin(elevationAngle);
    //centerY = sin(rotationAngle) * sin(elevationAngle);
    //centerZ = -cos(elevationAngle);

    vec3 move = {0};

    move[0] += control->kb[SDL_SCANCODE_W];
    move[0] -= control->kb[SDL_SCANCODE_S];
    move[2] -= control->kb[SDL_SCANCODE_A];
    move[2] += control->kb[SDL_SCANCODE_D];

    vec3_norm(move, move);
    float2_rot(move, move+2, yaw);
    vec3_scale(move, move, control->delta);

    vec3_add(player->pos, player->pos, move);
}