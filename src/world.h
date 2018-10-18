//
// Created by Thomas Lienbacher on 15.10.2018.
//

#ifndef CASTLEGAME3D_WORLD_H
#define CASTLEGAME3D_WORLD_H

#include <model.h>
#include <vector.h>
#include <text.h>
#include "switch.h"
#include "physics.h"

#define WORLD_SIZE 30.0f
#define NUM_ISWITCHES 4

typedef struct _world_s {
    texture_t *floorTex;
    mesh_t *floorMesh;
    model_t *floor;
    physicsbody_t floorBody;

    texture_t *skyboxTex;
    mesh_t *skyboxMesh;
    model_t *skybox;

    texture_t *wallTex;
    mesh_t *wallMesh;
    model_t *wall;

    vector_t *platforms;
    iswitch_t iswitches[NUM_ISWITCHES];

    texture_t *jewelTex;
    mesh_t *jewelMesh;
    model_t *jewel;
    int jewelCollected;

    font_t *font;
} world_t;

extern world_t g_world;

void world_init();
void world_update();
void world_render();
void world_quit();

#endif //CASTLEGAME3D_WORLD_H
