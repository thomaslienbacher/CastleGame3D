//
// Created by Thomas Lienbacher on 12.10.2018.
//

#include <render.h>
#include "game.h"
#include "engine.h"
#include "physics.h"

void game_init() {
    g_control.kb = SDL_GetKeyboardState(NULL);
    physics_init();
    world_init();
    player_init();
}

void game_update() {
    player_control();
    world_update();
    physics_update();

#ifdef DEBUG_BUILD
    char title[100];
    sprintf(title, TITLE " FPS: %f %f", 1.0f / g_control.delta, g_control.delta);
    SDL_SetWindowTitle(g_display->window, title);
#endif
}

void game_render() {
    camera_view(g_camera, (vec3) {g_player.body.pos[0], g_player.body.pos[1] + PLAYER_HEIGHT, g_player.body.pos[2]},
                g_player.pitch, g_player.yaw);

    mat4x4 projview;
    mat4x4_mul(projview, g_camera->projMat, g_camera->viewMat);
    program_unistr_mat(g_commonProg, "u_projview", projview);
    program_unistr_mat(g_skyboxProg, "u_view", g_camera->viewMat);
    program_unistr_mat(g_skyboxProg, "u_proj", g_camera->projMat);

    //input
    if (g_control.kb[SDL_SCANCODE_ESCAPE]) g_display->running = 0;

    world_render();
}

void game_quit() {
    physics_quit();
    world_quit();
}