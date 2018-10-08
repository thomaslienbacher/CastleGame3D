#include <render.h>
#include <program.h>
#include <display.h>
#include <camera.h>
#include <windows.h>
#include "settings.h"
#include "player.h"
#include "defs.h"

#undef main

int main(int argc, char** argv) {
    settings_t settings;
    settings_default(&settings);
    settings_file(&settings, "data/game.cfg");

    display_t *display = display_new("OpenGL", settings.width, settings.height, settings.fullscreen, settings.renderScale);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = CLEAR_COLOR[1] = CLEAR_COLOR[2] = CLEAR_COLOR[3] = 0.1f;

    //program
    program_t *program = program_new("data/vertex_shader.glsl", "data/fragment_shader.glsl");
    program_use(program);

    //camera
    camera_t *camera = camera_new(settings.fov, (float) display->width / display->height, 0.1f, 200);

    //quad_model
    texture_t *texture = texture_new("data/gun.png", GL_LINEAR, 4.0f);
    mesh_t *mesh = mesh_newobj("data/floor.obj");
    model_t *model = model_new(mesh, texture);

    //game vars
    SDL_SetWindowGrab(display->window, SDL_TRUE);
    SDL_ShowCursor(SDL_FALSE);
    struct control_s control = {0};
    control.kb = SDL_GetKeyboardState(NULL);

    player_t player;
    player_init(&player);

    int frame = 0;
    while (display->running) {
        frame++;
        float delta;
        display_prepare(display, &delta, settings.renderScale);

#ifdef DEBUG_BUILD
        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);
#endif
        
        //setting up control data
        int lmx = control.mx, lmy = control.my;
        control.delta = delta;
        control.button = SDL_GetMouseState(&control.mx, &control.my);
        control.dmx = (float)control.mx - lmx;
        control.dmy = (float)control.my - lmy;
        if(frame % 10) {
            if(display->hasFocus)SDL_WarpMouseInWindow(display->window, display->width / 2, display->height / 2);
            control.dmx += display->width / 2.f - control.mx;
            control.dmy += display->height / 2.f - control.my;
            control.dmx *= -1;
        }

        player_control(&player, &control);

        //camera lookto
        camera_lookto(camera, player.pos, player.lookto);

        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        //input
        if (control.kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //rendering
        program_use(program);

        for (int x = -5; x < 5; ++x) {
            for (int y = -5; y < 5; ++y) {
                model_mat(model, (float[]){x * 3.0f, -1, y * 3.0f}, (float[]){0,0,0}, 3.0f);
                program_unistr_mat(program, "u_model", model->mat);
                render_model(model);
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
