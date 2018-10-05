//
// Created by Thomas Lienbacher on 03.10.2018.
//

#ifndef CASTLEGAME3D_DEFS_H
#define CASTLEGAME3D_DEFS_H

#include <SDL2/SDL.h>

struct control_s {
    float delta;
    const Uint8 *kb;//keyboard
    int mx;//mouse x
    int my;//mouse y
    Uint32 button;//mouse button mask
};

#endif //CASTLEGAME3D_DEFS_H
