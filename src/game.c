//
// Created by Thomas Lienbacher on 12.10.2018.
//

#include <render.h>
#include "game.h"
#include "engine.h"

void game_init() {
    g_control.kb = SDL_GetKeyboardState(NULL);
    world_init(&world);
    player_init(&player);
}

void game_update() {
    player_control(&player, &g_control);

#ifdef DEBUG_BUILD
    char title[100];
    sprintf(title, "FPS: %f %f", 1.0f / g_control.delta, g_control.delta);
    SDL_SetWindowTitle(g_display->window, title);
#endif
}

void game_render() {
    camera_view(g_camera, player.pos, player.pitch, player.yaw);

    mat4x4 projview;
    mat4x4_mul(projview, g_camera->projMat, g_camera->viewMat);
    program_unistr_mat(g_commonProg, "u_projview", projview);
    program_unistr_mat(g_skyboxProg, "u_view", g_camera->viewMat);
    program_unistr_mat(g_skyboxProg, "u_proj", g_camera->projMat);
    program_unistr_f(g_commonProg, "u_uvscale", 1.0f);

    //input
    if (g_control.kb[SDL_SCANCODE_ESCAPE]) g_display->running = 0;

    //render floor
    program_use(g_commonProg);
    model_transform(world.floor, (float[]){-0.5f * 100.0f, 0, 0.5f * 100.f}, VEC3_ZERO, 100.0f);
    program_unistr_mat(g_commonProg, "u_model", world.floor->mat);
    program_unistr_f(g_commonProg, "u_uvscale", 30.0f);
    render_model(world.floor);

    //lastly render skybox
    glDisable(GL_CULL_FACE);
    program_use(g_skyboxProg);
    render_model(world.skybox);
    glEnable(GL_CULL_FACE);
}

void game_quit(){
    world_quit(&world);
}