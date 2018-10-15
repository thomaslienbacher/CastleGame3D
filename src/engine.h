//
// Created by Thomas Lienbacher on 15.10.2018.
//

#ifndef CASTLEGAME3D_ENGINE_H
#define CASTLEGAME3D_ENGINE_H

#include <camera.h>
#include <program.h>
#include <display.h>
#include "settings.h"


extern display_t *g_display;
extern program_t *g_commonProg, *g_skyboxProg;
extern camera_t *g_camera;

void engine_init();
void engine_quit();

#endif //CASTLEGAME3D_ENGINE_H
