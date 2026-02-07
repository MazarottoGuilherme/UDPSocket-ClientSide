#ifndef UDPSOCKETCLIENT_GAME_H
#define UDPSOCKETCLIENT_GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#define WIDTH_TILES 50
#define HEIGHT_TILES 36

void game_init(void);
void game_handle_event(SDL_Event *e);
void game_update(void);
void game_render(void);
void game_shutdown(void);

#endif //UDPSOCKETCLIENT_GAME_H