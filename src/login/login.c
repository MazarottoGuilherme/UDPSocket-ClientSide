/*
    Create by Kaua 02/02/2026
*/


#include "login.h"

SDL_Window *windowLogin = NULL;
SDL_Renderer *renderLogin = NULL;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

SDL_Rect inputBox   = { 50, 80, 300, 30 };
SDL_Rect buttonEnter = { 50, 130, 100, 40 };

// desenha o texto (label)
void drawText(SDL_Renderer *renderer, TTF_Font *font,
              const char *text, int x, int y, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = { x, y, surface->w, surface->h };

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

int checkButtonClick(int x, int y)
{
    return x >= buttonEnter.x && x <= buttonEnter.x + buttonEnter.w &&
           y >= buttonEnter.y && y <= buttonEnter.y + buttonEnter.h;
}

void drawUI(TTF_Font *font, const char *username)
{
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color gray  = {180, 180, 180, 255};

    SDL_SetRenderDrawColor(renderLogin, 0, 0, 0, 255);
    SDL_RenderClear(renderLogin);
    drawText(renderLogin, font, "Username:", 50, 50, white);
    SDL_SetRenderDrawColor(renderLogin, 50, 50, 50, 255);
    SDL_RenderFillRect(renderLogin, &inputBox);
    SDL_SetRenderDrawColor(renderLogin, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderLogin, &inputBox);
    drawText(renderLogin, font, username, inputBox.x + 5, inputBox.y + 5, white);
    SDL_SetRenderDrawColor(renderLogin, gray.r, gray.g, gray.b, 255);
    SDL_RenderFillRect(renderLogin, &buttonEnter);
    SDL_SetRenderDrawColor(renderLogin, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderLogin, &buttonEnter);
    drawText(renderLogin, font, "Entrar", buttonEnter.x + 20, buttonEnter.y + 10, white);

    SDL_RenderPresent(renderLogin);
}

char *EntryUser(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init erro: %s\n", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() != 0) {
        printf("TTF_Init erro: %s\n", TTF_GetError());
        return NULL;
    }

    windowLogin = SDL_CreateWindow("Login",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_SHOWN
    );

    renderLogin = SDL_CreateRenderer(windowLogin, -1, SDL_RENDERER_ACCELERATED);
    if (!windowLogin || !renderLogin) {
        printf("Erro janela/renderer\n");
        return NULL;
    }
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",18);
    if (!font) {
        printf("Erro fonte: %s\n", TTF_GetError());
        return NULL;
    }

    char *username = calloc(64, 1);
    int running = 1;

    SDL_StartTextInput();
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                free(username);
                username = NULL;
                running = 0;
            }
            else if (e.type == SDL_TEXTINPUT) {
                if (strlen(username) < 63)
                    strcat(username, e.text.text);
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(username) > 0)
                    username[strlen(username) - 1] = '\0';
                else if (e.key.keysym.sym == SDLK_RETURN)
                    running = 0;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (checkButtonClick(e.button.x, e.button.y))
                    running = 0;
            }
        }

        drawUI(font, username);
        SDL_Delay(16);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderLogin);
    SDL_DestroyWindow(windowLogin);
    TTF_Quit();
    SDL_Quit();

    return username;
}
