#include <render.h>
#include <program.h>
#include <display.h>
#include <camera.h>
#include <windows.h>
#include "settings.h"
#include "player.h"
#include "defs.h"

#undef main

int main(int argc, char **argv) {
    settings_t settings;
    settings_default(&settings);
    settings_file(&settings, "data/game.cfg");

    display_t *display = display_new("OpenGL", settings.width, settings.height, settings.fullscreen,
                                     settings.renderScale, settings.vsync);
    display_set_icon(display, "data/icon.png");

    CLEAR_COLOR[0] = CLEAR_COLOR[1] = CLEAR_COLOR[2] = CLEAR_COLOR[3] = 0.2f;

    //program
    program_t *commonProg = program_new("data/common_vs.glsl", "data/common_fs.glsl");
    program_t *skyboxProg = program_new("data/skybox_vs.glsl", "data/skybox_fs.glsl");

    //camera
    camera_t *camera = camera_new(settings.fov, (float) display->width / display->height, 0.1f, 200);

    //model
    texture_t *floorTex = texture_new("data/floor.png", GL_LINEAR, 4.0f);
    mesh_t *floorMesh = mesh_newobj("data/floor.obj");
    model_t *floor = model_new(floorMesh, floorTex);

    texture_t *skyboxTex = texture_new("data/skybox_blurred.png", GL_LINEAR, 1.0f);
    texture_wrap(skyboxTex, GL_CLAMP_TO_EDGE);
    mesh_t *skyboxMesh = mesh_newobj("data/cube.obj");
    model_t *skybox = model_new(skyboxMesh, skyboxTex);
    model_mat(skybox, (float[]) {0, 10, 0}, VEC3_ZERO, 100.0f);
    program_unistr_mat(skyboxProg, "u_model", skybox->mat);

    //game vars
    SDL_WarpMouseInWindow(display->window, display->width / 2, display->height / 2);
    struct control_s control = {0};
    control.kb = SDL_GetKeyboardState(NULL);

    player_t player;
    player_init(&player);

    char firstFrame = 1;

    while (display->running) {
        float delta;
        display_prepare(display, &delta, settings.renderScale);

        if(firstFrame) {
            SDL_GetMouseState(NULL, NULL);//eat movement event
            firstFrame = 0;
            continue;
        }

        //setting up control data
        if (display->hasFocus) {
            SDL_ShowCursor(SDL_FALSE);
            control.delta = delta;
            int lmx = control.mx, lmy = control.my;
            control.button = SDL_GetMouseState(&control.mx, &control.my);
            control.dmx = (float) control.mx - lmx;
            control.dmy = (float) control.my - lmy;
            SDL_WarpMouseInWindow(display->window, display->width / 2, display->height / 2);
            control.dmx += display->width / 2.f - control.mx;
            control.dmy += display->height / 2.f - control.my;
            control.dmx *= -1;
        }
        else {
            SDL_ShowCursor(SDL_TRUE);
            control.delta = control.dmx = control.dmy = 0;
            control.button = 0;
        }

        player_control(&player, &control);

        //camera lookto
        camera_view(camera, player.pos, player.pitch, player.yaw);

        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(commonProg, "u_projview", projview);
        program_unistr_mat(skyboxProg, "u_view", camera->viewMat);
        program_unistr_mat(skyboxProg, "u_proj", camera->projMat);
        program_unistr_f(commonProg, "u_uvscale", 1.0f);

        //input
        if (control.kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //render floor
        program_use(commonProg);
        model_mat(floor, (float[]){-0.5f * 100.0f, 1, 0.5f * 100.f}, VEC3_ZERO, 100.0f);
        program_unistr_mat(commonProg, "u_model", floor->mat);
        program_unistr_f(commonProg, "u_uvscale", 30.0f);
        render_model(floor);

        //lastly render skybox
        glDisable(GL_CULL_FACE);
        program_use(skyboxProg);
        render_model(skybox);
        glEnable(GL_CULL_FACE);

#ifdef DEBUG_BUILD
        char title[100];
        sprintf(title, "OpenGL FPS: %f %f", 1.0f / delta, delta);
        SDL_SetWindowTitle(display->window, title);
#endif

        display_show(display);
    }

    model_free(floor);
    mesh_free(floorMesh);
    texture_free(floorTex);
    model_free(skybox);
    mesh_free(skyboxMesh);
    texture_free(skyboxTex);
    camera_free(camera);
    program_free(commonProg);
    display_free(display);

    return 0;
}
