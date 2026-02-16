#ifndef UDPSOCKETCLIENT_PLAYERS_RENDER_H
#define UDPSOCKETCLIENT_PLAYERS_RENDER_H
#include <SDL_ttf.h>

#include "../net/net.h"
extern Player playerPrincipal;
void render_players(int cx, int cy, TTF_Font *font);
#endif //UDPSOCKETCLIENT_PLAYERS_RENDER_H