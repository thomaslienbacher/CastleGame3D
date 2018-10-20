//
// Created by Thomas Lienbacher on 15.10.2018.
//

#include <program.h>
#include <render.h>
#include "world.h"
#include "game.h"
#include "engine.h"
#include "switch.h"
#include "platform.h"

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
    model_transform(g_world.skybox, (float[]) {0, 25, 0}, VEC3_ZERO, 130.0f);
    program_unistr_mat(g_skyboxProg, "u_model", g_world.skybox->mat);

    g_world.wallTex = texture_new("data/wall.png", GL_LINEAR, 1.0f);
    texture_wrap(g_world.wallTex, GL_MIRRORED_REPEAT);
    g_world.wallMesh = mesh_newobj("data/wall_inv_normals.obj");
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

    vec3_cpy(g_world.iswitches[i].body.pos, (vec3) {0, 0, -3});
    model_transform(g_world.iswitches[i].model, g_world.iswitches[i].body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&g_world.iswitches[i].body);
    i++;

    vec3_cpy(g_world.iswitches[i].body.pos, (vec3) {-8, 17+PLATFORM_HEIGHT, -8});
    model_transform(g_world.iswitches[i].model, g_world.iswitches[i].body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&g_world.iswitches[i].body);
    i++;

    vec3_cpy(g_world.iswitches[i].body.pos, (vec3) {10.5, 22, 10.5});
    model_transform(g_world.iswitches[i].model, g_world.iswitches[i].body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&g_world.iswitches[i].body);
    i++;

    vec3_cpy(g_world.iswitches[i].body.pos, (vec3) {-2, 37+PLATFORM_HEIGHT, 7});
    model_transform(g_world.iswitches[i].model, g_world.iswitches[i].body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&g_world.iswitches[i].body);
    i++;

    //platforms
    g_world.platforms = vector_new(6);

    platform_t *plat = calloc(1, sizeof(platform_t));
    platform_init(plat, (vec3) {5, 20, 2});
    vector_push(g_world.platforms, plat);

    {
        platform_t *plat0 = calloc(1, sizeof(platform_t));
        platform_copy(plat, plat0, (vec3) {12, 13, -7});
        vector_push(g_world.platforms, plat0);
    }
    {
        platform_t *plat0 = calloc(1, sizeof(platform_t));
        platform_copy(plat, plat0, (vec3) {12, 27, 12});
        vector_push(g_world.platforms, plat0);
    }
    {
        platform_t *plat0 = calloc(1, sizeof(platform_t));
        platform_copy(plat, plat0, (vec3) {-8, 17, -8});
        vector_push(g_world.platforms, plat0);
    }
    {
        platform_t *plat0 = calloc(1, sizeof(platform_t));
        platform_copy(plat, plat0, (vec3) {0, 59, 0});
        vector_push(g_world.platforms, plat0);
    }

    //jewel
    jewel_init(&g_world.jewel, (vec3) {0, 60, 0});
}

void world_update() {
    if(iswitch_check(&g_world.iswitches[0])) {
        platform_animate(vector_get(g_world.platforms, 0), (vec3) {5, 6, 2});
    }
    if(iswitch_check(&g_world.iswitches[1])) {
        platform_animate(vector_get(g_world.platforms, 0), (vec3) {-3, 27, -3});
    }
    if(iswitch_check(&g_world.iswitches[2])) {
        platform_animate(vector_get(g_world.platforms, 0), (vec3) {0, 37, 7});
    }
    if(iswitch_check(&g_world.iswitches[3])) {
        platform_animate(vector_get(g_world.platforms, 0), (vec3) {0, 50, 7});
    }

    for (int i = 0; i < g_world.platforms->size; ++i) {
        platform_t *p = (platform_t *)vector_get(g_world.platforms, i);
        if (p) {
            platform_update(p);
        }
    }

    jewel_update(&g_world.jewel);
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
    program_unistr_vec2(g_commonProg, "u_uvscale", (float[]) {12.0f, 12.0f});
    render_model(g_world.floor);

    static int frame = 0;
    frame++;

    //iswitches
    program_unistr_vec2(g_commonProg, "u_uvscale", (float[]) {1.0f, 1.0f});
    for (int i = 0; i < NUM_ISWITCHES; ++i) {
        iswitch_render(&g_world.iswitches[i]);
    }

    for (int i = 0; i < g_world.platforms->size; ++i) {
        platform_t *p = (platform_t *)vector_get(g_world.platforms, i);
        if (p) {
            platform_render(p);
        }
    }

    jewel_render(&g_world.jewel);
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
