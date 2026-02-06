#ifndef UDPSOCKETCLIENT_GAME_STATE_H
#define UDPSOCKETCLIENT_GAME_STATE_H

static char username[64];
typedef struct {
    int id;
    char name[64];
} Usuario;

void set_username(const char *name);
const char *get_username(void);

#endif //UDPSOCKETCLIENT_GAME_STATE_H