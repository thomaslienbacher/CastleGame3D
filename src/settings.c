//
// Created by Thomas Lienbacher on 28.09.2018.
//

#include "settings.h"
#include <stdlib.h>
#include <stdio.h>
#include <filehelper.h>
#include <string.h>

void settings_default(settings_t *settings) {
    settings->width = 400;
    settings->height = 320;
    settings->renderScale = 1.0f;
    settings->fullscreen = 1;
    settings->fov = 80;
    settings->vsync = 1;
}

//:TODO: maybe remove code repetition
void settings_file(settings_t *settings, const char *filename) {
    FILE *file = fadv_open(filename, "r");

    char key[256];
    char value[256];

    while(fscanf(file, "%s %s", key, value) == 2) {
        if(key[0] == '#') continue;
        strupr(key);

        if(!strcmp(key, "WIDTH")) {
            int i = strtol(value, (char**)NULL, 10);
            if(i) settings->width = i;
        }
        if(!strcmp(key, "HEIGHT")) {
            int i = strtol(value, (char**)NULL, 10);
            if(i) settings->height = i;
        }
        if(!strcmp(key, "RENDERSCALE")) {
            float i = strtof(value, (char**)NULL);
            if(i) settings->renderScale = i;
        }
        if(!strcmp(key, "FULLSCREEN")) {
            int i = strtol(value, (char**)NULL, 10);
            if(i || (value[0] == '0')) settings->fullscreen = (char)i;
        }
        if(!strcmp(key, "FOV")) {
            float i = strtof(value, (char**)NULL);
            if(i) settings->fov = i;
        }
        if(!strcmp(key, "VSYNC")) {
            int i = strtol(value, (char**)NULL, 10);
            if(i || (value[0] == '0')) settings->vsync = (char)i;
        }
    }

    fadv_close(file);
}
