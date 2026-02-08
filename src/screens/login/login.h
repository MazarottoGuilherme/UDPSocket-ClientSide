#ifndef LOGIN_H
#define LOGIN_H

/*
    Create by Kaua 02/02/2026
    essa merda de codigo login n é pra mexer, deixa essa merda criar uma 
    tela pra ele msm, do outro jeito, ele n deixava as letra aparecer
*/



#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../net/net.h"
#include "../../render/render_objects.h"
#include "../../render/render.h"


SDL_Renderer* getRenderer(void);


extern SDL_Window* windowLogin;
extern SDL_Renderer* renderLogin;
extern int WINDOW_WIDTH_LOGIN;
extern int WINDOW_HEIGHT_LOGIN;

void login_init(void);
void login_shutdown(void);
void login_render(void);
void login_handle_event(SDL_Event* e);
void login_update(void);
void Login_user(SDL_Renderer* renderer);


#endif // LOGIN_H