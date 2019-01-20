#include <display.h>
#include "settings.h"
#include "player.h"
#include "game.h"
#include "engine.h"

int main(int argc, char *argv[]) {
    settings_load("data/game.cfg");

    engine_init();
    game_init();

    SDL_WarpMouseInWindow(g_display->window, g_display->width / 2, g_display->height / 2);
    char firstFrame = 1;

    while (g_display->running) {
        display_prepare(g_display, &g_control.delta, g_settings.renderScale);

        if (firstFrame) {
            SDL_GetMouseState(NULL, NULL);//eat movement event
            firstFrame = 0;
            continue;
        }

        //setting up control data
        if (g_display->hasFocus) {
            SDL_ShowCursor(SDL_FALSE);
            int lmx = g_control.mx, lmy = g_control.my;
            g_control.button = SDL_GetMouseState(&g_control.mx, &g_control.my);
            g_control.dmx = (float) g_control.mx - lmx;
            g_control.dmy = (float) g_control.my - lmy;
            SDL_WarpMouseInWindow(g_display->window, g_display->width / 2, g_display->height / 2);
            g_control.dmx += g_display->width / 2.f - g_control.mx;
            g_control.dmy += g_display->height / 2.f - g_control.my;
            g_control.dmx *= -1;

            game_update();
        } else {
            SDL_ShowCursor(SDL_TRUE);
            g_control.delta = g_control.dmx = g_control.dmy = 0;
            g_control.button = 0;
        }

        game_render();

        display_show(g_display);
    }

    game_quit();
    engine_quit();

    return 0;
}
