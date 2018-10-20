//
// Created by Thomas Lienbacher on 19.10.2018.
//

#include <time.h>
#include <render.h>
#include "platform.h"
#include "engine.h"
#include "defs.h"

void platform_init(platform_t *platform, vec3 pos) {
    platform->tex = texture_new("data/platform.png", GL_LINEAR, 1.0f);
    platform->mesh = mesh_newobj("data/platform.obj");
    platform->model = model_new(platform->mesh, platform->tex);

    vec3_cpy(platform->body.pos, pos);
    platform->body.height = PLATFORM_HEIGHT;
    platform->body.radius = 3.0f;
    physics_add_body(&platform->body);

    platform->time = 100.0f;
}

void platform_copy(platform_t *src, platform_t *dst, vec3 pos) {
    memcpy(dst, src, sizeof(platform_t));
    dst->model = model_new(src->mesh, src->tex);
    vec3_cpy(dst->body.pos, pos);
    physics_add_body(&dst->body);
}

void platform_animate(platform_t *platform, vec3 newPos) {
    vec3_cpy(platform->newPos, newPos);
    platform->time = 0;
}

void platform_update(platform_t *platform) {
    platform->time += g_control.delta;

    if(platform->time < 7.0f) {
        platform->body.pos[0] = mlinearf(platform->body.pos[0], platform->newPos[0], 1.1f * g_control.delta);
        platform->body.pos[1] = mlinearf(platform->body.pos[1], platform->newPos[1], 1.1f * g_control.delta);
        platform->body.pos[2] = mlinearf(platform->body.pos[2], platform->newPos[2], 1.1f * g_control.delta);
    }
}

void platform_render(platform_t *platform) {
    model_transform_as(platform->model, platform->body.pos, VEC3_ZERO, (vec3){3.0f, 1.0f, 3.0f});
    program_unistr_mat(g_commonProg, "u_model", platform->model->mat);
    render_model(platform->model);
}
