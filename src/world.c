//
// Created by Thomas Lienbacher on 15.10.2018.
//

#include <program.h>
#include <render.h>
#include "world.h"
#include "game.h"
#include "engine.h"
#include "switch.h"

world_t g_world;

void world_init() {
    //environment
    g_world.floorTex = texture_new("data/floor.png", GL_LINEAR, 4.0f);
    g_world.floorMesh = mesh_newobj("data/floor.obj");
    g_world.floor = model_new(g_world.floorMesh, g_world.floorTex);
    model_transform(g_world.floor, VEC3_ZERO, VEC3_ZERO, WORLD_SIZE);
    g_world.floorBody.pos[1] = -1;
    g_world.floorBody.radius = WORLD_SIZE * 2;
    g_world.floorBody.height = 1;
    physics_add_body(&g_world.floorBody);

    g_world.skyboxTex = texture_new("data/skybox_blurred.png", GL_NEAREST, 1.0f);
    texture_wrap(g_world.skyboxTex, GL_CLAMP_TO_EDGE);
    g_world.skyboxMesh = mesh_newobj("data/cube.obj");
    g_world.skybox = model_new(g_world.skyboxMesh, g_world.skyboxTex);
    model_transform(g_world.skybox, (float[]) {0, 25, 0}, VEC3_ZERO, 90.0f);
    program_unistr_mat(g_skyboxProg, "u_model", g_world.skybox->mat);

    g_world.wallTex = texture_new("data/wall.png", GL_LINEAR, 1.0f);
    texture_wrap(g_world.wallTex, GL_MIRRORED_REPEAT);
    g_world.wallMesh = mesh_newobj("data/wall.obj");
    g_world.wall = model_new(g_world.wallMesh, g_world.wallTex);
    model_transform_as(g_world.wall, (float[]) {0, -5, 0}, VEC3_ZERO, (float[]) {WORLD_SIZE, 12, WORLD_SIZE});

    //font
    g_world.font = font_new("data/consolas_32.csv", "data/consolas_32.png", FONT_DEFAULT_SCALAR);

    //switch
    iswitch_init(&g_world.iswitches[0]);
    iswitch_copy(&g_world.iswitches[0], &g_world.iswitches[1]);
    iswitch_copy(&g_world.iswitches[0], &g_world.iswitches[2]);
    iswitch_copy(&g_world.iswitches[0], &g_world.iswitches[3]);

    int i = 0;

    vec3_cpy(g_world.iswitches[i].body.pos, (vec3) {-13, 0, -13});
    model_transform(g_world.iswitches[i].model, g_world.iswitches[i].body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&g_world.iswitches[i].body); i++;

    vec3_cpy(g_world.iswitches[i].body.pos, (vec3) {-13, 0, 13});
    model_transform(g_world.iswitches[i].model, g_world.iswitches[i].body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&g_world.iswitches[i].body); i++;

    vec3_cpy(g_world.iswitches[i].body.pos, (vec3) {13, 0, 13});
    model_transform(g_world.iswitches[i].model, g_world.iswitches[i].body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&g_world.iswitches[i].body); i++;

    vec3_cpy(g_world.iswitches[i].body.pos, (vec3) {13, 0, -13});
    model_transform(g_world.iswitches[i].model, g_world.iswitches[i].body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&g_world.iswitches[i].body); i++;
}

void world_update() {
    for (int i = 0; i < NUM_ISWITCHES; ++i) {
        char c = iswitch_check(&g_world.iswitches[i]);
        if (c) printf("%d toggled\n", i);
    }
}

void world_render() {
    lightengine_upload(g_lightengine, g_commonProg);

    glDisable(GL_CULL_FACE);

    program_use(g_skyboxProg);
    render_model(g_world.skybox);

    program_use(g_commonProg);
    program_unistr_mat(g_commonProg, "u_model", g_world.wall->mat);
    program_unistr_vec2(g_commonProg, "u_uvscale", (float[]) {6.0f, 1.0f});
    render_model(g_world.wall);

    glEnable(GL_CULL_FACE);

    program_use(g_commonProg);
    program_unistr_mat(g_commonProg, "u_model", g_world.floor->mat);
    program_unistr_vec2(g_commonProg, "u_uvscale", (float[]) {15.0f, 15.0f});
    render_model(g_world.floor);

    static int frame = 0;
    frame++;

    //iswitches
    program_unistr_vec2(g_commonProg, "u_uvscale", (float[]) {1.0f, 1.0f});
    for (int i = 0; i < NUM_ISWITCHES; ++i) {
        iswitch_render(&g_world.iswitches[i]);
    }
}

void world_quit() {
    model_free(g_world.floor);
    mesh_free(g_world.floorMesh);
    texture_free(g_world.floorTex);

    model_free(g_world.skybox);
    mesh_free(g_world.skyboxMesh);
    texture_free(g_world.skyboxTex);

    model_free(g_world.wall);
    mesh_free(g_world.wallMesh);
    texture_free(g_world.wallTex);
}
