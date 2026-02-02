#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "net/net.h"
#include "render/render.h"
#include "login/login.h"

float player_x = 100;
float player_y = 100;

int main() {

    char *username = EntryUser();

    // gambiarra pra verificar o nome (funciona)
    int tamanhoName = strlen(username);
    if(tamanhoName < 1){
        return -1;
    }

    socket_init();
    initRenderer();

    int running = 1;
    SDL_Event e;

    //send_login();

    while (running) {

        /* INPUT */
        int dx = 0, dy = 0;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W]) dy = -1;
        if (keys[SDL_SCANCODE_S]) dy =  1;
        if (keys[SDL_SCANCODE_A]) dx = -1;
        if (keys[SDL_SCANCODE_D]) dx =  1;

        if (dx || dy)
            send_input(dx, dy);

        receive_packets();


        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(getRenderer());

        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (!players[i].active)
                continue;

            SDL_Rect r = { (int)players[i].x, (int)players[i].y, 50, 50 };

            // opcional: pinta o player local de vermelho e os outros de azul
            if (players[i].id == user_id) {
                SDL_SetRenderDrawColor(getRenderer(), 255, 0, 0, 255); // vermelho
            } else {
                SDL_SetRenderDrawColor(getRenderer(), 0, 0, 255, 255); // azul
            }

            SDL_RenderFillRect(getRenderer(), &r);
        }

        SDL_RenderPresent(getRenderer());

        SDL_Delay(16);
    }

    send_logout();
    // close(sock);
    SDL_Quit();
    return 0;
}
