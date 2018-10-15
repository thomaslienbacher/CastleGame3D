//
// Created by Thomas Lienbacher on 15.10.2018.
//

#ifndef CASTLEGAME3D_WORLD_H
#define CASTLEGAME3D_WORLD_H

#include <model.h>

#define WORLD_SIZE 30.0f

typedef struct _world_s {
    texture_t *floorTex;
    mesh_t *floorMesh;
    model_t *floor;

    texture_t *skyboxTex;
    mesh_t *skyboxMesh;
    model_t *skybox;

    texture_t *wallTex;
    mesh_t *wallMesh;
    model_t *wall;
} world_t;

extern world_t world;

void world_init();
void world_render();
void world_quit();

#endif //CASTLEGAME3D_WORLD_H
