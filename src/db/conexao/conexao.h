#ifndef CONEXAO_H
#define CONEXA_H


/*
    Create by Kaua 03/02/2026
*/


#include <postgresql/libpq-fe.h>
#include <stdlib.h>
#include <string.h>


extern PGconn *conn;


int bancoDeDados();


#endif // CONEXAO_H