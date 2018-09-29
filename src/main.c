#include <render.h>
#include <program.h>
#include "master.h"
#include "display.h"
#include "camera.h"
#include "settings.h"

void cam_control(camera_t *camera) {
    const Uint8 *kb = SDL_GetKeyboardState(NULL);

    static float x = 0;
    static float y = 0;
    static float z = 0;
    vec3 pos = {x, y, z};
    float a = 0.05f;
    if (kb[SDL_SCANCODE_W]) z -= a;
    if (kb[SDL_SCANCODE_S]) z += a;
    if (kb[SDL_SCANCODE_A]) x -= a;
    if (kb[SDL_SCANCODE_D]) x += a;
    if (kb[SDL_SCANCODE_Q]) y += a;
    if (kb[SDL_SCANCODE_E]) y -= a;
    //printf("pos: %f %f %f\n", x, y, z);

    static float xr = 0;
    static float yr = 0;
    static float zr = 0;
    vec3 rot = {xr, yr, zr};
    float r = 0.4f;
    if (kb[SDL_SCANCODE_I]) xr -= r;
    if (kb[SDL_SCANCODE_K]) xr += r;
    if (kb[SDL_SCANCODE_J]) yr -= r;
    if (kb[SDL_SCANCODE_L]) yr += r;
    if (kb[SDL_SCANCODE_U]) zr += r;
    if (kb[SDL_SCANCODE_O]) zr -= r;
    //printf("rot: %f %f %f\n", xr, yr, zr);

    if (kb[SDL_SCANCODE_R]) {
        xr = yr = zr = 0;
    }

    camera_view(camera, pos, rot[0], rot[1], rot[2]);
}

#undef main

int main(int argc, char** argv) {

    settings_t settings;
    settings_default(&settings);
    settings_file(&settings, "data/game.cfg");

    display_t *display = display_new("OpenGL", settings.width, settings.height, settings.fullscreen, settings.renderScale);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = 0.1f;
    CLEAR_COLOR[1] = 0.1f;
    CLEAR_COLOR[2] = 0.1f;
    CLEAR_COLOR[3] = 0.1f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(settings.fov, (float) display->width / display->height, 0.1f, 200);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_LINEAR, 1);
    mesh_t *mesh = mesh_newobj("data/gun.obj");
    model_t *model = model_new(mesh, texture);

    while (display->running) {
        float delta;
        display_prepare(display, &delta, settings.renderScale);

        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);

        const Uint8 *kb = SDL_GetKeyboardState(NULL);

        cam_control(camera);
        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        //input
        if (kb[SDL_SCANCODE_TAB]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //render
        program_use(program);

        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                for (int z = 0; z < 4; ++z) {
                    model_mat(model, (float[]){x * 3.4f, y * 3.2f, z * 4}, (float[]){0,0,0}, 0.8f);
                    program_unistr_mat(program, "u_model", model->mat);
                    render_model(model);
                }
            }
        }

        display_show(display);
    }

    model_free(model);
    mesh_free(mesh);
    texture_free(texture);
    camera_free(camera);
    program_free(program);
    display_free(display);

    return 0;
}
