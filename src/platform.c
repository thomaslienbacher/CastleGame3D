//
// Created by Thomas Lienbacher on 19.10.2018.
//

#include <render.h>
#include "platform.h"
#include "engine.h"
#include "game.h"

platform_t *platform_new(texture_t *texture, mesh_t *mesh, vec3 pos) {
    platform_t *platform = te_calloc(1, sizeof(platform_t));

    platform->tex = texture;
    platform->mesh = mesh;
    platform->model = model_new(platform->mesh, platform->tex);

    vec3_cpy(platform->body.pos, pos);
    platform->body.height = PLATFORM_HEIGHT;
    platform->body.radius = 3.0f;
    physics_add_body(&platform->body);

    platform->time = 100.0f;

    return platform;
}

void platform_animate(platform_t *platform, vec3 newPos) {
    vec3_cpy(platform->newPos, newPos);
    platform->time = 0;
}

void platform_update(platform_t *platform) {
    platform->time += g_control.delta;

    if (platform->time < 7.0f) {
        platform->body.pos[0] = mlinearf(platform->body.pos[0], platform->newPos[0], 1.1f * g_control.delta);
        platform->body.pos[1] = mlinearf(platform->body.pos[1], platform->newPos[1], 1.1f * g_control.delta);
        platform->body.pos[2] = mlinearf(platform->body.pos[2], platform->newPos[2], 1.1f * g_control.delta);
    }
}

void platform_render(platform_t *platform) {
    model_transform_as(platform->model, platform->body.pos, VEC3_ZERO, (vec3) {3.0f, 1.0f, 3.0f});
    program_unistr_mat(g_commonProg, "u_model", platform->model->mat);
    render_model(platform->model);
}

void platform_free(platform_t *platform) {
    model_free(platform->model);
    te_free(platform);
}
