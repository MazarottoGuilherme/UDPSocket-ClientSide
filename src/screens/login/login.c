#include "login.h"

#include <SDL_ttf.h>
#include <string.h>

#include "../../game/game_state.h"
#include "../../render/render_objects.h"
#include "../screen.h"

static struct {
    char username[64];
    char password[64];
    TTF_Font *font;
    int finished;
    int activeField;
} login;

SDL_Rect inputBoxEmail   = { 50, 80, 300, 30 };
SDL_Rect inputBoxPassword   = { 50, 80, 300, 30 };
SDL_Rect buttonEnter = { 50, 130, 100, 40 };


void login_init(void) {
    memset(&login, 0, sizeof(login));
    login.activeField = 0;

    login.font = TTF_OpenFont(ASSETS_DIR "/DejaVuSans-BoldOblique.ttf", 18);
    if (!login.font) {
        printf("Font error: %s\n", TTF_GetError());
        exit(1);
    }
}

void login_handle_event(SDL_Event *e) {
    if (e->type == SDL_TEXTINPUT) {
        if (login.activeField == 0 && strlen(login.username) < 63)
            strcat(login.username, e->text.text);
        else if (login.activeField == 1 && strlen(login.password) < 63)
            strcat(login.password, e->text.text);
    }

    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_RETURN:
                login.finished = 1;
                break;
            case SDLK_TAB:
                login.activeField = 1 - login.activeField;
                break;
            case SDLK_BACKSPACE:
                if (login.activeField == 0 && strlen(login.username) > 0)
                    login.username[strlen(login.username) - 1] = '\0';
                else if (login.activeField == 1 && strlen(login.password) > 0)
                    login.password[strlen(login.password) - 1] = '\0';
                break;
        }
    }
}

void login_update(void) {
    int id_user;
    if (login.finished) {
        id_user = send_login(login.username, login.password, Usuario *user );
        if(id_user > 0){
            set_username(login.username);
            user->id = id_user;
            change_screen(SCREEN_GAME);
        }
        else{
            return;
        }
    }
}

void login_render(void) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color gray  = {180, 180, 180, 255};
    SDL_Color activeColor = {100, 100, 255, 255};
    drawText(login.font, "Email:", 50, 50, white);
    drawText(login.font, "Senha:", 50, 110, white);

    fill_rect(&inputBoxEmail, (SDL_Color){50, 50, 50, 255});
    draw_rect(&inputBoxEmail, login.activeField == 0 ? activeColor : white);
    drawText(login.font, login.username,
             inputBoxEmail.x + 5, inputBoxEmail.y + 5, white);
    fill_rect(&inputBoxPassword, (SDL_Color){50, 50, 50, 255});
    draw_rect(&inputBoxPassword, login.activeField == 1 ? activeColor : white);

    // não mostra a senha
    char masked[64];
    memset(masked, '*', strlen(login.password));
    masked[strlen(login.password)] = '\0';
    drawText(login.font, masked,
             inputBoxPassword.x + 5, inputBoxPassword.y + 5, white);
    fill_rect(&buttonEnter, gray);
    draw_rect(&buttonEnter, white);
    drawText(login.font, "Entrar",
             buttonEnter.x + 20, buttonEnter.y + 10, white);
}


void login_shutdown(void) {
    TTF_CloseFont(login.font);
}