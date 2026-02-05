#include "../screens/screen.h"

#include "game/game.h"
#include "login/login.h"

static ScreenType current = SCREEN_LOGIN;

void change_screen(ScreenType next) {
    if (current == SCREEN_LOGIN)
        login_shutdown();
    if (current == SCREEN_GAME)
        game_shutdown();

    current = next;

    if (current == SCREEN_LOGIN)
        login_init();
    if (current == SCREEN_GAME)
        game_init();
}

void screen_handle_event(SDL_Event *e) {
    if (current == SCREEN_LOGIN)
        login_handle_event(e);
    if (current == SCREEN_GAME)
        game_handle_event(e);
}

void screen_update(void) {
    if (current == SCREEN_LOGIN)
        login_update();
    if (current == SCREEN_GAME)
        game_update();
}


void screen_render(void) {
    if (current == SCREEN_LOGIN)
        login_render();
    if (current == SCREEN_GAME)
        game_render();
}
