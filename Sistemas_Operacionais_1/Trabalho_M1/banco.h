#ifndef BANCO_H
#define BANCO_H

#define PIPE_NAME "/tmp/pipe_db"
#define MAX_BUFFER 256
#define MAX_NOME 50

#define THREAD_POOL_SIZE 4
#define QUEUE_SIZE 10

typedef struct {
    int id;
    char nome[MAX_NOME];
} Registro;

#endif