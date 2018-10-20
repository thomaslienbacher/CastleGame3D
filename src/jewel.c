//
// Created by Thomas Lienbacher on 20.10.2018.
//

#include <render.h>
#include "jewel.h"
#include "engine.h"
#include "defs.h"
#include "player.h"

void jewel_init(jewel_t *jewel, vec3 pos) {
    jewel->tex = texture_new("data/jewel.png", GL_LINEAR, 1.0f);
    jewel->mesh = mesh_newobj("data/jewel.obj");
    jewel->model = model_new(jewel->mesh, jewel->tex);

    model_transform(jewel->model, pos, VEC3_ZERO, 1.3f);
    vec3_cpy(jewel->model->pos, pos);
    jewel->pickedUp = 0;
}

void jewel_update(jewel_t *jewel) {
    jewel->time += g_control.delta;
    model_transform(jewel->model, (vec3){jewel->model->pos[0], jewel->model->pos[1] + sinf(jewel->time * 2) / 4.0f, jewel->model->pos[2]},
                    (vec3){0, jewel->time * 90, 0}, 1.3f);

    vec3 tmp;
    vec3_sub(tmp, g_player.body.pos, jewel->model->pos);

    if(vec3_lens(tmp) < JEWEL_PICKUP_DIST*JEWEL_PICKUP_DIST) {
        jewel->pickedUp = 1;
    }
}

void jewel_render(jewel_t *jewel) {
    if(jewel->pickedUp) return;

    program_unistr_mat(g_commonProg, "u_model", jewel->model->mat);
    render_model(jewel->model);
}
