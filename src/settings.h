//
// Created by Thomas Lienbacher on 28.09.2018.
//

#ifndef CASTLEGAME3D_SETTINGS_H
#define CASTLEGAME3D_SETTINGS_H

/**
 * settings file structure:
 * key value
 * # is a comment
 */
typedef struct _settings_s {
    int width, height;
    float renderScale;
    char fullscreen;
    float fov;
    char vsync;
} settings_t;

extern settings_t g_settings;

void settings_load(const char *filename);

#endif //CASTLEGAME3D_SETTINGS_H
