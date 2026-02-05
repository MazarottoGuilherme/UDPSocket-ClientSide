#ifndef UDPSOCKETCLIENT_LOGIN_H
#define UDPSOCKETCLIENT_LOGIN_H
#include <SDL2/SDL.h>

void login_init(void);
void login_handle_event(SDL_Event *e);
void login_update(void);
void login_render(void);
void login_shutdown(void);
#endif //UDPSOCKETCLIENT_LOGIN_H