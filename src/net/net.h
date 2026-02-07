#ifndef UDPSOCKETCLIENT_NET_H
#define UDPSOCKETCLIENT_NET_H

#define MAX_PLAYERS 1024
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int active;
    int id;
    float x, y;
}Player;

extern Player players[MAX_PLAYERS];

extern int user_id;

void socket_init();
void send_login();
void send_input(int dx, int dy);
void receive_packets();
void send_logout();
void net_send(void *data, size_t size);
void send_ping(uint32_t now);
int net_update(void);
#endif //UDPSOCKETCLIENT_NET_H