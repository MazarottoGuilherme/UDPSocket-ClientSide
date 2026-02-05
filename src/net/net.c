#include "net.h"

#include <errno.h>

#include "../protocol/protocol.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int sock;
struct sockaddr_in server_addr;
socklen_t addr_len;

Player players[MAX_PLAYERS];

int user_id = 0;

void socket_init() {
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_len = sizeof(server_addr);
}

void send_login() {
    PacketLogin pkt;
    memset(&pkt, 0, sizeof(pkt));

    pkt.type = PKT_LOGIN;
    strncpy(pkt.username, "guilherme", 15);

    sendto(sock, &pkt, sizeof(pkt), 0,
           (struct sockaddr*)&server_addr, addr_len);
}

void send_input(int dx, int dy) {
    PacketInput pkt;
    pkt.type = PKT_INPUT;
    pkt.dx = dx;
    pkt.dy = dy;

    sendto(sock, &pkt, sizeof(pkt), 0,
           (struct sockaddr*)&server_addr, addr_len);
}

void send_logout() {
    PacketLogout pkt;
    pkt.type = PKT_LOGOUT;
    pkt.id = user_id;

    sendto(sock, &pkt, sizeof(pkt), 0, (struct sockaddr*)&server_addr, addr_len);
}

void handle_state_packet(PacketState* pkt) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].active && players[i].id == pkt->player_id) {
            // atualiza posição existente
            players[i].x = pkt->x;
            players[i].y = pkt->y;
            return; // terminou
        }
    }

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].active) {
            players[i].active = 1;
            players[i].id = pkt->player_id;
            players[i].x = pkt->x;
            players[i].y = pkt->y;
            return;
        }
    }

}

void receive_packets() {
    uint8_t buffer[512];
    ssize_t received;

    while (1) {
        received = recvfrom(
            sock,
            buffer,
            sizeof(buffer),
            0,
            NULL,
            NULL
        );

        if (received < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
                break;
            perror("recvfrom");
            break;
        }

        PacketHeader* hdr = (PacketHeader*)buffer;

        if (hdr->type == PKT_STATE) {
            PacketState* pkt = (PacketState*)buffer;
            handle_state_packet(pkt);
        }else if ( hdr->type == PKT_LOGIN_ACK ) {
            PacketLoginACK* ack = (PacketLoginACK*)buffer;
            user_id = ack->id;
        }else if (hdr->type == PKT_LOGOUT) {
            PacketLogout* pkt = (PacketLogout*)buffer;

            for (int i = 0; i < MAX_PLAYERS; i++) {
                if (players[i].active && players[i].id == pkt->id) {
                    players[i].active = 0;  // remove da lista
                    break;
                }
            }
        }
    }
}