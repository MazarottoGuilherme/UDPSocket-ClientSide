#include "engine.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "../render/render.h"

void engine_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) exit(1);
    if (TTF_Init() != 0) exit(1);

    initRenderer("Game");
    SDL_StartTextInput();
}

void engine_shutdown() {
    SDL_StopTextInput();
    destroyRenderer();
    TTF_Quit();
    SDL_Quit();
}
