/*
    Create by Kaua 02/02/2026
*/

#include "login.h"

SDL_Window *windowLogin = NULL;
SDL_Renderer *renderLogin = NULL;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

SDL_Rect emailBox    = { 50, 80, 300, 30 };
SDL_Rect passBox     = { 50, 140, 300, 30 };
SDL_Rect buttonEnter = { 50, 200, 100, 40 };


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

int insideRect(int x, int y, SDL_Rect r)
{
    return x >= r.x && x <= r.x + r.w &&
           y >= r.y && y <= r.y + r.h;
}

void drawUI(TTF_Font *font, const char *email, const char *password)
{
    SDL_Color white = {255,255,255,255};
    SDL_Color gray  = {180,180,180,255};

    SDL_SetRenderDrawColor(renderLogin, 0,0,0,255);
    SDL_RenderClear(renderLogin);

    drawText(renderLogin, font, "Email:", 50, 50, white);
    drawText(renderLogin, font, "Password:", 50, 110, white);

    SDL_SetRenderDrawColor(renderLogin, 50,50,50,255);
    SDL_RenderFillRect(renderLogin, &emailBox);
    SDL_RenderFillRect(renderLogin, &passBox);

    SDL_SetRenderDrawColor(renderLogin, 255,255,255,255);
    SDL_RenderDrawRect(renderLogin, &emailBox);
    SDL_RenderDrawRect(renderLogin, &passBox);

    drawText(renderLogin, font, email, emailBox.x+5, emailBox.y+5, white);

    char masked[64];
    memset(masked, '*', strlen(password));
    masked[strlen(password)] = '\0';
    drawText(renderLogin, font, masked, passBox.x+5, passBox.y+5, white);

    SDL_SetRenderDrawColor(renderLogin, gray.r, gray.g, gray.b, 255);
    SDL_RenderFillRect(renderLogin, &buttonEnter);
    SDL_SetRenderDrawColor(renderLogin, 255,255,255,255);
    SDL_RenderDrawRect(renderLogin, &buttonEnter);
    drawText(renderLogin, font, "Entrar", buttonEnter.x+20, buttonEnter.y+10, white);

    SDL_RenderPresent(renderLogin);
}

char *EntryUser(Usuario *user)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    windowLogin = SDL_CreateWindow(
        "Login",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    renderLogin = SDL_CreateRenderer(windowLogin, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 18
    );

    char *email = calloc(64,1);
    char *password = calloc(64,1);
    int active = 0; // 0=email , 1=password
    int running = 1;

    SDL_StartTextInput();
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT) {
                free(email);
                free(password);
                return NULL;
            }

            // button da tela
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (insideRect(e.button.x, e.button.y, emailBox))
                    active = 0;
                else if (insideRect(e.button.x, e.button.y, passBox))
                    active = 1;
                else if (insideRect(e.button.x, e.button.y, buttonEnter)){
                    int resultado = SearchID(email, password, user);
                    if (resultado > 0) {running = 0; } else if (resultado == 0) {
                        printf("Erro: Email ou senha incorretos.\n");
                    } else {
                        printf("Erro de validação ou banco: Codigo %d\n", resultado);
                    }
                }  
            }

            else if (e.type == SDL_TEXTINPUT) {
                if (active == 0 && strlen(email) < 63)
                    strcat(email, e.text.text);
                else if (active == 1 && strlen(password) < 63)
                    strcat(password, e.text.text);
            }

            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    if (active == 0 && strlen(email) > 0)
                        email[strlen(email)-1] = '\0';
                    else if (active == 1 && strlen(password) > 0)
                        password[strlen(password)-1] = '\0';
                }
                else if (e.key.keysym.sym == SDLK_RETURN)
                    running = 0;
            }
        }

        drawUI(font, email, password);
        SDL_Delay(16);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderLogin);
    SDL_DestroyWindow(windowLogin);
    TTF_Quit();
    SDL_Quit();

    return email;
}