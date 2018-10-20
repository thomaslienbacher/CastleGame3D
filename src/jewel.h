//
// Created by Thomas Lienbacher on 20.10.2018.
//

#ifndef CASTLEGAME3D_JEWEL_H
#define CASTLEGAME3D_JEWEL_H

#include <model.h>

#define JEWEL_HEIGHT 0.5f
#define JEWEL_PICKUP_DIST 0.6f

typedef struct _jewel_s {
    texture_t *tex;
    mesh_t *mesh;
    model_t *model;
    float time;
    char pickedUp;
} jewel_t;

void jewel_init(jewel_t *jewel, vec3 pos);
void jewel_update(jewel_t *jewel);
void jewel_render(jewel_t *jewel);

#endif //CASTLEGAME3D_JEWEL_H
