//
// Created by Thomas Lienbacher on 15.10.2018.
//

#include <render.h>
#include "engine.h"
#include "world.h"
#include "game.h"

display_t *g_display;
program_t *g_commonProg, *g_skyboxProg, *g_fontProg;
camera_t *g_camera;
lightengine_t *g_lightengine;

void engine_init() {
    g_display = display_new(TITLE, g_settings.width, g_settings.height, g_settings.fullscreen, g_settings.renderScale,
                            g_settings.vsync);
    display_set_icon(g_display, "data/icon.png");

    CLEAR_COLOR[0] = 0.7f;
    CLEAR_COLOR[1] = 0.7f;
    CLEAR_COLOR[2] = 0.7f;
    CLEAR_COLOR[3] = 0.0f;

    //program
    g_commonProg = program_new("data/common_vs.glsl", "data/common_fs.glsl");
    g_skyboxProg = program_new("data/skybox_vs.glsl", "data/skybox_fs.glsl");
    g_fontProg = program_new("data/font_vs.glsl", "data/font_fs.glsl");

    g_camera = camera_new(g_settings.fov, (float) g_display->width / (float) g_display->height, 0.2f, 300.0f);
    g_lightengine = lightengine_new(g_commonProg, NUM_ISWITCHES + 1);
}

void engine_quit() {
    camera_free(g_camera);
    program_free(g_commonProg);
    program_free(g_skyboxProg);
    program_free(g_fontProg);
    lightengine_free(g_lightengine);
    display_free(g_display);
}
