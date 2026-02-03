#ifndef LOGIN_USER_H
#define LOGIN_USER_H


#include "../conexao/conexao.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char email[256];
    char password[100];
} Usuario;

int SearchID(const char *email, const char *password, Usuario *usuario);


#endif // LOGIN_USER_H