//
// Created by Thomas Lienbacher on 12.10.2018.
//

#ifndef CASTLEGAME3D_GAME_H
#define CASTLEGAME3D_GAME_H

#include <SDL2/SDL.h>
#include <tengine_math.h>

struct control_s {
    float delta;
    const Uint8 *kb;//keyboard
    int mx;//mouse x
    int my;//mouse y
    float dmx;//delta mouse x since last frame still and int
    float dmy;//            y
    Uint32 button;//mouse button mask
};

extern struct control_s g_control;

#define TITLE "Castle Jumping 3D"

void game_init();

void game_update();

void game_render();

void game_quit();


#endif //CASTLEGAME3D_GAME_H
