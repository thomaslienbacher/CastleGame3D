//
// Created by Thomas Lienbacher on 17.10.2018.
//

#include <render.h>
#include "iswitch.h"
#include "engine.h"
#include "world.h"
#include "player.h"
#include "game.h"

iswitch_t *iswitch_new(texture_t *texRed, texture_t *texGreen, mesh_t *mesh, vec3 pos) {
    iswitch_t *iswitch = te_calloc(1, sizeof(iswitch_t));

    iswitch->texRed = texRed;
    iswitch->texGreen = texGreen;
    iswitch->mesh = mesh;
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

    return iswitch;
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

void iswitch_free(iswitch_t *iswitch) {
    text_free(iswitch->text);
    model_free(iswitch->model);
    te_free(iswitch);
}
