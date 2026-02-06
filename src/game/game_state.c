#include "../game/game_state.h"

#include <string.h>


void set_username(const char *name) {
    strncpy(username, name, sizeof(username) - 1);
}

const char *get_username(void) {
    return username;
}
