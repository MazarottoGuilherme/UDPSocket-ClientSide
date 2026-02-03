#include "conexao.h"

/*
    Create by Kaua 03/02/2026
*/


PGconn *conn = NULL;

int bancoDeDados() {
    const char *params[] = {"host", "port", "dbname", "user", "password", NULL};
    const char *values[] = {"localhost", "5432", "postgres", "postgres", "5115", NULL};

    conn = PQconnectdbParams(params, values, 0);

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Erro ao conectar ao banco de dados: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        conn = NULL; 
        return 1;
    }

    printf("Conexão estabelecida com sucesso!\n");
    return 0;
}