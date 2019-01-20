//
// Created by Thomas Lienbacher on 19.10.2018.
//

#ifndef CASTLEGAME3D_PLATFORM_H
#define CASTLEGAME3D_PLATFORM_H

#include <model.h>
#include "physics.h"

#define PLATFORM_HEIGHT 0.5f

typedef struct _platform_s {
    physicsbody_t body;
    texture_t *tex;
    mesh_t *mesh;
    model_t *model;
    float time;
    vec3 newPos;
} platform_t;

void platform_init(platform_t *platform, vec3 pos);

void platform_copy(platform_t *src, platform_t *dst, vec3 pos);

void platform_animate(platform_t *platform, vec3 newPos);

void platform_update(platform_t *platform);

void platform_render(platform_t *platform);

#endif //CASTLEGAME3D_PLATFORM_H
