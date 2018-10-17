//
// Created by Thomas Lienbacher on 15.10.2018.
//

#include <program.h>
#include <render.h>
#include "world.h"
#include "game.h"
#include "engine.h"

world_t world;

void world_init() {
    world.floorTex = texture_new("data/floor.png", GL_LINEAR, 4.0f);
    world.floorMesh = mesh_newobj("data/floor.obj");
    world.floor = model_new(world.floorMesh, world.floorTex);
    model_transform(world.floor, VEC3_ZERO, VEC3_ZERO, WORLD_SIZE);

    world.skyboxTex = texture_new("data/skybox_blurred.png", GL_LINEAR, 1.0f);
    texture_wrap(world.skyboxTex, GL_CLAMP_TO_EDGE);
    world.skyboxMesh = mesh_newobj("data/cube.obj");
    world.skybox = model_new(world.skyboxMesh, world.skyboxTex);
    model_transform(world.skybox, (float[]) {0, 15, 0}, VEC3_ZERO, 90.0f);
    program_unistr_mat(g_skyboxProg, "u_model", world.skybox->mat);

    world.wallTex = texture_new("data/wall.png", GL_LINEAR, 1.0f);
    texture_wrap(world.wallTex, GL_MIRRORED_REPEAT);
    world.wallMesh = mesh_newobj("data/wall.obj");
    world.wall = model_new(world.wallMesh, world.wallTex);
    model_transform_as(world.wall, (float[]) {0, -5, 0}, VEC3_ZERO, (float[]) {WORLD_SIZE, 12, WORLD_SIZE});
}

void world_render() {
    program_use(g_commonProg);
    program_unistr_mat(g_commonProg, "u_model", world.floor->mat);
    program_unistr_vec2(g_commonProg, "u_uvscale", (float[]) {15.0f, 15.0f});
    render_model(world.floor);

    glDisable(GL_CULL_FACE);

    program_use(g_skyboxProg);
    render_model(world.skybox);

    program_use(g_commonProg);
    program_unistr_mat(g_commonProg, "u_model", world.wall->mat);
    program_unistr_vec2(g_commonProg, "u_uvscale", (float[]) {6.0f, 1.0f});
    render_model(world.wall);

    glEnable(GL_CULL_FACE);
}

void world_quit() {
    model_free(world.floor);
    mesh_free(world.floorMesh);
    texture_free(world.floorTex);

    model_free(world.skybox);
    mesh_free(world.skyboxMesh);
    texture_free(world.skyboxTex);

    model_free(world.wall);
    mesh_free(world.wallMesh);
    texture_free(world.wallTex);
}
