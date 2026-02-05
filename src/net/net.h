#ifndef UDPSOCKETCLIENT_NET_H
#define UDPSOCKETCLIENT_NET_H

#define MAX_PLAYERS 1024

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
#endif //UDPSOCKETCLIENT_NET_H