//
// Created by Thomas Lienbacher on 18.10.2018.
//

#ifndef CASTLEGAME3D_PHYSICS_H
#define CASTLEGAME3D_PHYSICS_H

#include <vector.h>
#include <tengine_math.h>

#define GRAVITY (-12.0f)
#define SPACING 0.003f

typedef struct _physicsbody_s {
    vec3 pos;
    vec3 vel;
    float height, radius;
} physicsbody_t;

typedef struct _physicsengine_s {
    physicsbody_t *player;
    vector_t *bodys;
    int steps;
} physicsengine_t;

extern physicsengine_t g_physicsengine;

void physics_init();

void physics_add_body(physicsbody_t *physicsbody);

char physics_colliding(physicsbody_t *a, physicsbody_t *b);

void physics_update();

void physics_quit();

#endif //CASTLEGAME3D_PHYSICS_H
