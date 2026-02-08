#include "login.h"


SDL_Renderer* renderLogin = NULL;
static TTF_Font* font = NULL;

SDL_Rect emailBox    = {50, 80, 300, 30};
SDL_Rect passBox     = {50, 140, 300, 30};
SDL_Rect buttonEnter = {50, 200, 100, 40};


static char email[64] = {0};
static char password[64] = {0};
static int activeBox = -1;

static int insideRect(int x, int y, SDL_Rect r){
    return x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h;
}

static void drawText(const char* text, int x, int y, SDL_Color color){
    if(!text || !font || !renderLogin) return;

    SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text, color);
    if(!surf) return;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderLogin, surf);
    SDL_Rect dst = {x, y, surf->w, surf->h};
    SDL_FreeSurface(surf);

    SDL_RenderCopy(renderLogin, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
}

void login_init(void){
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 18);
    if(!font){
        printf("Erro ao abrir fonte: %s\n", TTF_GetError());
        exit(1);
    }
}


void login_shutdown(void){
    if(font) TTF_CloseFont(font);
}


void login_render(void){
    SDL_Color white = {255,255,255,255};
    SDL_Color gray  = {180,180,180,255};
    SDL_Color activeColor = {70,70,70,255};

    SDL_SetRenderDrawColor(renderLogin, 0, 0, 0, 255);
    SDL_RenderClear(renderLogin);
    drawText("Email:", 50, 50, white);
    drawText("Senha:", 50, 110, white);
    SDL_SetRenderDrawColor(renderLogin,
        activeBox==0?activeColor.r:50,
        activeBox==0?activeColor.g:50,
        activeBox==0?activeColor.b:50, 255);
    SDL_RenderFillRect(renderLogin, &emailBox);

    SDL_SetRenderDrawColor(renderLogin,
        activeBox==1?activeColor.r:50,
        activeBox==1?activeColor.g:50,
        activeBox==1?activeColor.b:50, 255);
    SDL_RenderFillRect(renderLogin, &passBox);

    SDL_SetRenderDrawColor(renderLogin, 255,255,255,255);
    SDL_RenderDrawRect(renderLogin, &emailBox);
    SDL_RenderDrawRect(renderLogin, &passBox);
    drawText(email, emailBox.x+5, emailBox.y+5, white);

    char masked[64] = {0};
    for(int i=0;i<strlen(password);i++) masked[i]='*';
    drawText(masked, passBox.x+5, passBox.y+5, white);
    SDL_SetRenderDrawColor(renderLogin, gray.r, gray.g, gray.b, 255);
    SDL_RenderFillRect(renderLogin, &buttonEnter);
    SDL_SetRenderDrawColor(renderLogin, 255,255,255,255);
    SDL_RenderDrawRect(renderLogin, &buttonEnter);
    drawText("Entrar", buttonEnter.x+20, buttonEnter.y+10, white);

    SDL_RenderPresent(renderLogin);
}

void login_handle_event(SDL_Event* e){
    switch(e->type){
        case SDL_QUIT:
            exit(0);

        case SDL_MOUSEBUTTONDOWN:
            if(insideRect(e->button.x, e->button.y, emailBox)) activeBox=0;
            else if(insideRect(e->button.x, e->button.y, passBox)) activeBox=1;
            else if(insideRect(e->button.x, e->button.y, buttonEnter))
                printf("Entrar clicado!\nEmail: %s\nSenha: %s\n", email, password);
            else activeBox=-1;
            break;

        case SDL_TEXTINPUT:
            if(activeBox==0 && strlen(email)+strlen(e->text.text)<sizeof(email))
                strcat(email, e->text.text);
            if(activeBox==1 && strlen(password)+strlen(e->text.text)<sizeof(password))
                strcat(password, e->text.text);
            break;

        case SDL_KEYDOWN:
            if(e->key.keysym.sym == SDLK_BACKSPACE){
                if(activeBox==0 && strlen(email)>0) email[strlen(email)-1]='\0';
                if(activeBox==1 && strlen(password)>0) password[strlen(password)-1]='\0';
            }
            break;
    }
}

void login_update(void){}


void Login_user(SDL_Renderer* renderer){
    renderLogin = renderer;
    login_init();

    SDL_StartTextInput();
    SDL_Event e;
    int running = 1;

    while(running){
        while(SDL_PollEvent(&e))
            login_handle_event(&e);

        login_update();
        login_render();

        SDL_Delay(16);
    }

    SDL_StopTextInput();
    login_shutdown();
}
