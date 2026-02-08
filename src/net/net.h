#ifndef UDPSOCKETCLIENT_NET_H
#define UDPSOCKETCLIENT_NET_H

#define MAX_PLAYERS 1024


#include <stddef.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include "../protocol/protocol.h"
#include <fcntl.h>
#include <SDL_timer.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../game/game_state.h"


typedef struct {
    int active;
    int id;
    float x, y;
}Player;

extern Player players[MAX_PLAYERS];

extern int user_id;
// Usua

void socket_init();
int send_login(char *email, char *password);
void send_input(int dx, int dy);
void receive_packets();
void send_logout();
void net_send(void *data, size_t size);
void send_ping(uint32_t now);
int net_update(void);
#endif //UDPSOCKETCLIENT_NET_H