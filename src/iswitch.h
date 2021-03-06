//
// Created by Thomas Lienbacher on 17.10.2018.
//

#ifndef CASTLEGAME3D_INTERACTION_H
#define CASTLEGAME3D_INTERACTION_H

#include <model.h>
#include <text.h>
#include "physics.h"

#define ISWITCH_RED 0
#define ISWITCH_GREEN 1
#define ISWITCH_DIST 2.7f
#define ISWITCH_DEACT_TIME 3.0f

typedef struct _switch_s {
    physicsbody_t body;
    texture_t *texRed;
    texture_t *texGreen;
    mesh_t *mesh;
    model_t *model;
    text_t *text;
    char state;
    float time;
    int lightId;
} iswitch_t;

void iswitch_init(iswitch_t *iswitch, vec3 pos);

void iswitch_copy(iswitch_t *src, iswitch_t *dst, vec3 pos);

char iswitch_check(iswitch_t *iswitch);

void iswitch_render(iswitch_t *iswitch);

#endif //CASTLEGAME3D_INTERACTION_H
