//
// Created by Thomas Lienbacher on 17.10.2018.
//

#include <render.h>
#include "switch.h"
#include "engine.h"
#include "world.h"

void iswitch_init(iswitch_t *iswitch) {
    iswitch->texRed = texture_new("data/switch_red.png", GL_LINEAR, 1.0f);
    iswitch->texGreen = texture_new("data/switch_green.png", GL_LINEAR, 1.0f);
    iswitch->mesh = mesh_newobj("data/switch.obj");
    iswitch->model = model_new(iswitch->mesh, iswitch->texRed);
    iswitch->text = text_new(g_world.font, "Press F to toggle");
    iswitch->lightId = lightengine_get_id(g_lightengine);
}

void iswitch_copy(iswitch_t *src, iswitch_t *dst) {
    memcpy(dst, src, sizeof(iswitch_t));
    src->model = model_new(src->mesh, src->texRed);
    src->lightId = lightengine_get_id(g_lightengine);
}

void iswitch_render(iswitch_t *iswitch) {
    lightengine_set(g_lightengine, iswitch->lightId, iswitch->state == ISWITCH_GREEN ? VEC3_UNITY : VEC3_UNITX,
            (float[]){iswitch->model->pos[0], iswitch->model->pos[1]+2.5f, iswitch->model->pos[2]}, 0.7f);

    iswitch->model->texture = iswitch->state == ISWITCH_GREEN ? iswitch->texGreen : iswitch->texRed;
    program_unistr_mat(g_commonProg, "u_model", iswitch->model->mat);
    render_model(iswitch->model);
}
