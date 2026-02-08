#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "net/net.h"
#include "render/render.h"
#include "engine/engine.h"
#include "screens/screen.h"
#include <unistd.h>



float player_x = 100;
float player_y = 100;


int main() {

    socket_init();
    initRenderer("Game");

    int running = 1;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;

            screen_handle_event(&e);
        }
        screen_update();

        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(getRenderer());

        screen_render();

        SDL_RenderPresent(getRenderer());

        SDL_Delay(16);

    }

    send_logout();

    engine_shutdown();
    return 0;
}
