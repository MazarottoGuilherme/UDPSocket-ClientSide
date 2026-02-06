#ifndef UDPSOCKETCLIENT_NET_H
#define UDPSOCKETCLIENT_NET_H

#define MAX_PLAYERS 1024
#include "../game/game_state.h"

typedef struct {
    int active;
    int id;
    float x, y;
}Player;

extern Player players[MAX_PLAYERS];

extern int user_id;
Usua

void socket_init();
void send_login(char *email, char *password);
void send_input(int dx, int dy);
void receive_packets();
void send_logout();
#endif //UDPSOCKETCLIENT_NET_H