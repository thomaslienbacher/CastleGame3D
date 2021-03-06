//
// Created by Thomas Lienbacher on 17.10.2018.
//

#include <render.h>
#include "iswitch.h"
#include "engine.h"
#include "world.h"
#include "player.h"

void iswitch_init(iswitch_t *iswitch, vec3 pos) {
    iswitch->texRed = texture_new("data/switch_red.png", GL_LINEAR, 1.0f);
    iswitch->texGreen = texture_new("data/switch_green.png", GL_LINEAR, 1.0f);
    iswitch->mesh = mesh_newobj("data/switch.obj");
    iswitch->model = model_new(iswitch->mesh, iswitch->texRed);
    iswitch->text = text_new(g_world.font, "Press F to activate");
    text_transform(iswitch->text, (vec2) {-iswitch->text->width / 2 * 0.8f, -0.7f}, 0.8f);
    iswitch->lightId = lightengine_get_id(g_lightengine);
    iswitch->state = 0;

    vec3_cpy(iswitch->body.pos, pos);
    model_transform(iswitch->model, iswitch->body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&iswitch->body);

    iswitch->body.height = 1.f;
    iswitch->body.radius = 0.6f;
}

void iswitch_copy(iswitch_t *src, iswitch_t *dst, vec3 pos) {
    memcpy(dst, src, sizeof(iswitch_t));
    dst->model = model_new(src->mesh, src->texRed);
    dst->lightId = lightengine_get_id(g_lightengine);
    vec3_cpy(dst->body.pos, pos);
    model_transform(dst->model, dst->body.pos, VEC3_ZERO, 1.0f);
    physics_add_body(&dst->body);
}

char iswitch_check(iswitch_t *iswitch) {
    iswitch->time -= g_control.delta;

    if (iswitch->time <= 0) {
        vec3 tmp;
        vec3_sub(tmp, g_player.body.pos, iswitch->model->pos);

        if (g_control.kb[SDL_SCANCODE_F] && vec3_lens(tmp) < ISWITCH_DIST * ISWITCH_DIST) {
            if (!iswitch->state) {
                iswitch->state = 1;
                iswitch->time = ISWITCH_DEACT_TIME;

                return 1;
            }
        }

        iswitch->state = 0;
    }

    return 0;
}

void iswitch_render(iswitch_t *iswitch) {
    vec3_cpy(iswitch->model->pos, iswitch->body.pos);

    lightengine_set(g_lightengine, iswitch->lightId, iswitch->state == ISWITCH_GREEN ? VEC3_UNITY : VEC3_UNITX,
                    (float[]) {iswitch->model->pos[0], iswitch->model->pos[1] + 2.5f, iswitch->model->pos[2]}, 1.3f);

    iswitch->model->texture = iswitch->state == ISWITCH_GREEN ? iswitch->texGreen : iswitch->texRed;
    program_unistr_mat(g_commonProg, "u_model", iswitch->model->mat);
    render_model(iswitch->model);

    vec3 tmp;
    vec3_sub(tmp, g_player.body.pos, iswitch->model->pos);

    if (vec3_lens(tmp) < ISWITCH_DIST * ISWITCH_DIST && !iswitch->state) {
        program_use(g_fontProg);
        program_unistr_mat(g_fontProg, "u_transform", iswitch->text->mat);
        glDisable(GL_DEPTH_TEST);
        render_text(iswitch->text);
        glEnable(GL_DEPTH_TEST);
    }
}
