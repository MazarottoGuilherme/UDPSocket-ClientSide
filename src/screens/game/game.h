#ifndef UDPSOCKETCLIENT_GAME_H
#define UDPSOCKETCLIENT_GAME_H
#include <SDL_events.h>

void game_init(void);
void game_handle_event(SDL_Event *e);
void game_update(void);
void game_render(void);
void game_shutdown(void);

#endif //UDPSOCKETCLIENT_GAME_H