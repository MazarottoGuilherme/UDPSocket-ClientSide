#ifndef UDPSOCKETCLIENT_SCREEN_H
#define UDPSOCKETCLIENT_SCREEN_H
#include <SDL2/SDL.h>

typedef enum {
    SCREEN_LOGIN,
    SCREEN_GAME
} ScreenType;

void change_screen(ScreenType next);

void screen_handle_event(SDL_Event *e);
void screen_update(void);
void screen_render(void);

#endif //UDPSOCKETCLIENT_SCREEN_H