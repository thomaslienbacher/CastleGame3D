//
// Created by Thomas Lienbacher on 15.10.2018.
//

#include <program.h>
#include "world.h"
#include "game.h"
#include "engine.h"

world_t world;

void world_init() {
    world.floorTex = texture_new("data/floor.png", GL_LINEAR, 4.0f);
    world.floorMesh = mesh_newobj("data/floor.obj");
    world.floor = model_new(world.floorMesh, world.floorTex);

    world.skyboxTex = texture_new("data/skybox_blurred.png", GL_LINEAR, 1.0f);
    texture_wrap(world.skyboxTex, GL_CLAMP_TO_EDGE);
    world.skyboxMesh = mesh_newobj("data/cube.obj");
    world.skybox = model_new(world.skyboxMesh, world.skyboxTex);
    model_transform(world.skybox, (float[]) {0, 30, 0}, VEC3_ZERO, 100.0f);
    program_unistr_mat(g_skyboxProg, "u_model", world.skybox->mat);
}

void world_quit() {
    model_free(world.floor);
    mesh_free(world.floorMesh);
    texture_free(world.floorTex);
    model_free(world.skybox);
    mesh_free(world.skyboxMesh);
    texture_free(world.skyboxTex);
}
