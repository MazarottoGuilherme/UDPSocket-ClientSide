#include <stdint.h>

#ifndef UDPSOCKETCLIENT_PROTOCOL_H
#define UDPSOCKETCLIENT_PROTOCOL_H

typedef enum {
    PKT_LOGIN = 1,
    PKT_INPUT = 2,
    PKT_PING  = 3,
    PKT_STATE = 4,
    PKT_LOGIN_ACK = 5,
    PKT_LOGOUT = 6,
    PKT_PONG = 7,
} PacketType;

typedef struct {
    uint8_t type;
} PacketHeader;

typedef struct {
    uint8_t type;
    char username[16];
} PacketLogin;

typedef struct {
    uint8_t type;
    int dx;
    int dy;
} PacketInput;

typedef struct {
    uint8_t type;
    int id;
} PacketLogout;

typedef struct {
    uint8_t type;
    int id;
} PacketLoginACK;

typedef struct {
    uint8_t type;
    uint32_t timestamp;
} PacketPing;

typedef struct {
    uint8_t type;
    uint32_t timestamp;
} PacketPong;

typedef struct {
    uint8_t type;
    int player_id;
    float x;
    float y;
} PacketState;

#endif //UDPSOCKETCLIENT_PROTOCOL_H