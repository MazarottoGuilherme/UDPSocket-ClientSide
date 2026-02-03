#ifndef LOGIN_H
#define LOGIN_H

/*
    Create by Kaua 02/02/2026
*/



#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// importando função de login do db
#include "../db/login/loginUser.h"

extern SDL_Window* windowLogin;
extern SDL_Renderer* renderLogin;
extern int WINDOW_WIDTH_LOGIN;
extern int WINDOW_HEIGHT_LOGIN;


void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color);
void drawUI(TTF_Font *font, const char *username, const char *password);
int checkButtonClick(int x, int y);
char* EntryUser(Usuario *user);

#endif // LOGIN_H
