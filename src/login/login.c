#include "login.h"




SDL_Window* windowLogin;
SDL_Renderer* renderLogin;
int WINDOW_WIDTH_LOGIN = 800;
int WINDOW_HEIGHT_LOGIN = 600;

SDL_Rect buttonEnter = {50, 120, 100, 40};

// desenha texto no renderer
void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = { x, y, surface->w, surface->h };
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

// verifica se o botão foi clicado
int checkButtonClick(int x, int y) {
    return x >= buttonEnter.x && x <= buttonEnter.x + buttonEnter.w &&
           y >= buttonEnter.y && y <= buttonEnter.y + buttonEnter.h;
}

// desenha a labels, input e botão
void drawUI(TTF_Font *font, const char *username) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color gray = {200, 200, 200, 255};
    SDL_Color black = {0, 0, 0, 255};

    SDL_SetRenderDrawColor(renderLogin, 0, 0, 0, 255);
    SDL_RenderClear(renderLogin);

    drawText(renderLogin, font, "Username:", 50, 50, white);

    SDL_Rect inputBox = {50, 80, 300, 30};
    SDL_SetRenderDrawColor(renderLogin, 50, 50, 50, 255);
    SDL_RenderFillRect(renderLogin, &inputBox);
    SDL_SetRenderDrawColor(renderLogin, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderLogin, &inputBox);

    char displayText[70];
    if (strlen(username) == 0)
        strcpy(displayText, "");
    else
        strcpy(displayText, username);


    // Botão Entrar
    SDL_SetRenderDrawColor(renderLogin, gray.r, gray.g, gray.b, 255);
    SDL_RenderFillRect(renderLogin, &buttonEnter);
    SDL_SetRenderDrawColor(renderLogin, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderLogin, &buttonEnter);
    drawText(renderLogin, font, "Entrar", buttonEnter.x + 15, buttonEnter.y + 10, white);

    SDL_RenderPresent(renderLogin);
}

// função de login, cria a janela
char* EntryUser() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erro SDL_Init: %s\n", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() != 0) {
        printf("Erro TTF_Init: %s\n", TTF_GetError());
        return NULL;
    }

    windowLogin = SDL_CreateWindow("Login",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   WINDOW_WIDTH_LOGIN,
                                   WINDOW_HEIGHT_LOGIN,
                                   SDL_WINDOW_SHOWN);
    renderLogin = SDL_CreateRenderer(windowLogin, -1, SDL_RENDERER_ACCELERATED);

    if (!windowLogin || !renderLogin) {
        printf("Erro ao criar janela/renderer: %s\n", SDL_GetError());
        return NULL;
    }

    TTF_Font *font = TTF_OpenFont("UDPSocket-ClientSide/src/login/DejaVuSans-BoldOblique.ttf", 18);
    if (!font) {
        printf("Falha ao abrir fonte: %s\n", TTF_GetError());
        return NULL;
    }

    char *username = malloc(64);
    username[0] = '\0';
    int usernameLen = 0;

    SDL_StartTextInput();

    int running = 1;
    SDL_Event e;
    int cursorVisible = 1;
    Uint32 lastCursorToggle = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                free(username);
                username = NULL;
                running = 0;
            }
            else if (e.type == SDL_TEXTINPUT) {
                if (usernameLen < 63) {
                    strcat(username, e.text.text);
                    usernameLen = strlen(username);
                }
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && usernameLen > 0) {
                    username[usernameLen-1] = '\0';
                    usernameLen--;
                }
                else if (e.key.keysym.sym == SDLK_RETURN) {
                    running = 0;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (checkButtonClick(e.button.x, e.button.y)) {
                    running = 0;
                }
            }
        }
        if (SDL_GetTicks() - lastCursorToggle > 500) {
            cursorVisible = !cursorVisible;
            lastCursorToggle = SDL_GetTicks();
        }

        drawUI(font, username);
        SDL_Delay(16);
    }

    SDL_StopTextInput();
    SDL_DestroyRenderer(renderLogin);
    SDL_DestroyWindow(windowLogin);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return username;
}
