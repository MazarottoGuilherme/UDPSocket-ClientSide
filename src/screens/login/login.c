#include "login.h"

#include <SDL_ttf.h>
#include <string.h>

#include "../../game/game_state.h"
#include "../../render/render_objects.h"
#include "../screen.h"

static struct {
    char username[64];
    TTF_Font *font;
    int finished;
} login;

SDL_Rect inputBox   = { 50, 80, 300, 30 };
SDL_Rect buttonEnter = { 50, 130, 100, 40 };

void login_init(void) {
    memset(&login, 0, sizeof(login));
    login.font = TTF_OpenFont(ASSETS_DIR "/DejaVuSans-BoldOblique.ttf", 18);
    if (!login.font) {
        printf("Font error: %s\n", TTF_GetError());
        exit(1);
    }
}

void login_handle_event(SDL_Event *e) {
    if (e->type == SDL_TEXTINPUT) {
        if (strlen(login.username) < 63)
            strcat(login.username, e->text.text);
    }

    if (e->type == SDL_KEYDOWN &&
        e->key.keysym.sym == SDLK_RETURN) {
        login.finished = 1;
    }
}


void login_update(void) {
    if (login.finished) {
        set_username(login.username);
        change_screen(SCREEN_GAME);
    }
}

void login_render(void) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color gray  = {180, 180, 180, 255};

    drawText(login.font, "Username:", 50, 50, white);


    fill_rect(&inputBox, (SDL_Color){50, 50, 50, 255});
    draw_rect(&inputBox, white);

    drawText(login.font, login.username,
             inputBox.x + 5, inputBox.y + 5, white);

    fill_rect(&buttonEnter, gray);
    draw_rect(&buttonEnter, white);

    drawText(login.font, "Entrar",
             buttonEnter.x + 20, buttonEnter.y + 10, white);
}

void login_shutdown(void) {
    TTF_CloseFont(login.font);
}