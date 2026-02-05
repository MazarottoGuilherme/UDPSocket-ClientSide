#include "game.h"
#include "../../net/net.h"
#include "../../render/render_objects.h"


void game_init(void) {
    socket_init();
    send_login();
}

void game_handle_event(SDL_Event *e) {

}

void game_update(void) {
    int dx = 0, dy = 0;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W]) dy = -1;
    if (keys[SDL_SCANCODE_S]) dy =  1;
    if (keys[SDL_SCANCODE_A]) dx = -1;
    if (keys[SDL_SCANCODE_D]) dx =  1;

    if (dx || dy)
        send_input(dx, dy);

    receive_packets();

}

void game_render(void) {
    SDL_Color c;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].active)
            continue;
        SDL_Rect r = { (int)players[i].x, (int)players[i].y, 50, 50 };

        if (players[i].id == user_id)
            c = (SDL_Color){255, 0,0,255};
        else
            c = (SDL_Color){0,0,255,255};

        fill_rect(&r, c);

    }
}

void game_shutdown(void) {

}