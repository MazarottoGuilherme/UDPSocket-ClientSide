#include "loginUser.h"



int SearchID(const char *email, const char *password, Usuario *usuario) {
    printf("acessou o searchID \n");
    // validando a conexao
    if (conn == NULL || PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Erro: Banco de dados não conectado.\n");
        return -4; 
    }

    size_t tamanhoEmail = strlen(email);
    if (tamanhoEmail < 3) {
        return -1;
    }

    size_t tamanhoPassword = strlen(password);
    if (tamanhoPassword < 4) {
        return -2; 
    }

    // preparando a query,l para evitar sql injection
    const char *params[2] = {email, password};
    
    PGresult *res = PQexecParams(conn,"SELECT id, email, password FROM usuario WHERE email = $1 AND password = $2", 2,NULL,params,NULL,NULL,0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro na Query: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return -3;
    }
    if (PQntuples(res) == 0) {
        PQclear(res);
        return 0; // Usuário ou senha incorretos
    }

    usuario->id = atoi(PQgetvalue(res, 0, 0));
    
    strncpy(usuario->email, PQgetvalue(res, 0, 1), sizeof(usuario->email) - 1);
    usuario->email[sizeof(usuario->email) - 1] = '\0';
    
    strncpy(usuario->password, PQgetvalue(res, 0, 2), sizeof(usuario->password) - 1);
    usuario->password[sizeof(usuario->password) - 1] = '\0';

    printf("Login bem-sucedido! Usuário ID: %d\n", usuario->id);

    PQclear(res);
    return usuario->id; // Retorna o ID
}