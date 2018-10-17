//
// Created by Thomas Lienbacher on 28.09.2018.
//

#include "settings.h"
#include <stdlib.h>
#include <stdio.h>
#include <filehelper.h>
#include <string.h>

settings_t g_settings;

void settings_load(const char *filename) {
    g_settings.width = 800;
    g_settings.height = 640;
    g_settings.renderScale = 1.0f;
    g_settings.fullscreen = 0;
    g_settings.fov = 90;
    g_settings.vsync = 1;

    FILE *file = fopen(filename, "r");
    if(!file) return;

    char key[256];
    char value[256];

    while(fscanf(file, "%s %s", key, value) == 2) {
        if(key[0] == '#') continue;
        strupr(key);

        if(!strcmp(key, "WIDTH")) {
            int i = strtol(value, (char**)NULL, 10);
            if(i) g_settings.width = i;
        }
        if(!strcmp(key, "HEIGHT")) {
            int i = strtol(value, (char**)NULL, 10);
            if(i) g_settings.height = i;
        }
        if(!strcmp(key, "RENDERSCALE")) {
            float i = strtof(value, (char**)NULL);
            if(i) g_settings.renderScale = i;
        }
        if(!strcmp(key, "FULLSCREEN")) {
            int i = strtol(value, (char**)NULL, 10);
            if(i || (value[0] == '0')) g_settings.fullscreen = (char)i;
        }
        if(!strcmp(key, "FOV")) {
            float i = strtof(value, (char**)NULL);
            if(i) g_settings.fov = i;
        }
        if(!strcmp(key, "VSYNC")) {
            int i = strtol(value, (char**)NULL, 10);
            if(i || (value[0] == '0')) g_settings.vsync = (char)i;
        }
    }

    fadv_close(file);
}
