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

    //model
    texture_t *floorTex = texture_new("data/floor.png", GL_LINEAR, 4.0f);
    mesh_t *floorMesh = mesh_newobj("data/floor.obj");
    model_t *floor = model_new(floorMesh, floorTex);

    texture_t *skyboxTex = texture_new("data/skybox_blurred.png", GL_LINEAR, 1.0f);
    texture_wrap(skyboxTex, GL_CLAMP_TO_EDGE);
    mesh_t *skyboxMesh = mesh_newobj("data/cube.obj");
    model_t *skybox = model_new(skyboxMesh, skyboxTex);
    model_mat(skybox, (float[]){0, 10, 0}, VEC3_ZERO, 45.0f);

    //game vars
    if(display->hasFocus) SDL_SetWindowGrab(display->window, SDL_TRUE);
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
        if(display->hasFocus) SDL_WarpMouseInWindow(display->window, display->width / 2, display->height / 2);
        control.dmx += display->width / 2.f - control.mx;
        control.dmy += display->height / 2.f - control.my;
        control.dmx *= -1;

        player_control(&player, &control);

        //camera lookto
        camera_view(camera, player.pos, player.pitch, player.yaw);

        mat4x4 projview;
        mat4x4_mul(projview, camera->projMat, camera->viewMat);
        program_unistr_mat(program, "u_projview", projview);

        //input
        if (control.kb[SDL_SCANCODE_ESCAPE]) display->running = 0;

        //rendering
        program_use(program);

        for (int x = -5; x < 5; ++x) {
            for (int y = -5; y < 5; ++y) {
                model_mat(floor, (float[]){x * 6.0f, -1, y * 6.0f}, (float[]){0,0,0}, 6.0f);
                program_unistr_mat(program, "u_model", floor->mat);
                render_model(floor);
            }
        }

        //lastly render skybox
        glDisable(GL_CULL_FACE);

        program_unistr_mat(program, "u_model", skybox->mat);
        render_model(skybox);//TODO: create own shader

        glEnable(GL_CULL_FACE);

        display_show(display);
    }

    model_free(floor);
    mesh_free(floorMesh);
    texture_free(floorTex);
    model_free(skybox);
    mesh_free(skyboxMesh);
    texture_free(skyboxTex);
    camera_free(camera);
    program_free(program);
    display_free(display);

    return 0;
}
