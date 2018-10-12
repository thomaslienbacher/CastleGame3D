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

void settings_default(settings_t *settings);
void settings_file(settings_t *settings, const char *filename);

#endif //CASTLEGAME3D_SETTINGS_H
