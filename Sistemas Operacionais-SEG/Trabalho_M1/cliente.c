#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <errno.h>
#include "banco.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// ===== FILA =====
char fila[QUEUE_SIZE][MAX_BUFFER];
int inicio = 0, fim = 0;

pthread_mutex_t fila_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// ===== LOG =====
void log_operacao(const char *msg) {
    pthread_mutex_lock(&mutex);

    FILE *log = fopen("log.txt", "a");
    if (log) {
        fprintf(log, "%s\n", msg);
        fclose(log);
    }

    pthread_mutex_unlock(&mutex);
}

// ===== OPERAÇÕES =====
void inserir(int id, char *nome) {
    FILE *f = fopen("banco.txt", "a");
    if (!f) return;

    fprintf(f, "%d %s\n", id, nome);
    fclose(f);

    char log_msg[100];
    sprintf(log_msg, "INSERT %d %s", id, nome);
    log_operacao(log_msg);
}

void selecionar(int id) {
    FILE *f = fopen("banco.txt", "r");
    if (!f) return;

    int fid;
    char nome[MAX_NOME];

    int encontrou = 0;

    while (fscanf(f, "%d %s", &fid, nome) != EOF) {
        if (fid == id) {
            printf("[SELECT] %d %s\n", fid, nome);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("[SELECT] ID %d não encontrado\n", id);

    fclose(f);
}

void deletar(int id) {
    FILE *f = fopen("banco.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!f || !temp) return;

    int fid;
    char nome[MAX_NOME];

    while (fscanf(f, "%d %s", &fid, nome) != EOF) {
        if (fid != id)
            fprintf(temp, "%d %s\n", fid, nome);
    }

    fclose(f);
    fclose(temp);

    remove("banco.txt");
    rename("temp.txt", "banco.txt");

    char log_msg[100];
    sprintf(log_msg, "DELETE %d", id);
    log_operacao(log_msg);
}

void atualizar(int id, char *nome) {
    FILE *f = fopen("banco.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!f || !temp) return;

    int fid;
    char nome_atual[MAX_NOME];

    while (fscanf(f, "%d %s", &fid, nome_atual) != EOF) {
        if (fid == id)
            fprintf(temp, "%d %s\n", fid, nome);
        else
            fprintf(temp, "%d %s\n", fid, nome_atual);
    }

    fclose(f);
    fclose(temp);

    remove("banco.txt");
    rename("temp.txt", "banco.txt");

    char log_msg[100];
    sprintf(log_msg, "UPDATE %d %s", id, nome);
    log_operacao(log_msg);
}

// ===== WORKER =====
void* worker(void *arg) {
    while (1) {
        pthread_mutex_lock(&fila_mutex);

        while (inicio == fim)
            pthread_cond_wait(&cond, &fila_mutex);

        char comando[MAX_BUFFER];
        strcpy(comando, fila[inicio]);

        inicio = (inicio + 1) % QUEUE_SIZE;

        pthread_mutex_unlock(&fila_mutex);

        printf("Recebido: %s\n", comando);

        pthread_mutex_lock(&mutex);

        if (strncmp(comando, "INSERT", 6) == 0) {
            int id;
            char nome[MAX_NOME];
            sscanf(comando, "INSERT %d %s", &id, nome);
            inserir(id, nome);
        }
        else if (strncmp(comando, "SELECT", 6) == 0) {
            int id;
            sscanf(comando, "SELECT %d", &id);
            selecionar(id);
        }
        else if (strncmp(comando, "DELETE", 6) == 0) {
            int id;
            sscanf(comando, "DELETE %d", &id);
            deletar(id);
        }
        else if (strncmp(comando, "UPDATE", 6) == 0) {
            int id;
            char nome[MAX_NOME];
            sscanf(comando, "UPDATE %d %s", &id, nome);
            atualizar(id, nome);
        }

        pthread_mutex_unlock(&mutex);
    }
}

// ===== MAIN =====
int main() {
    int fd;
    char buffer[MAX_BUFFER];

    // Criar pipe (ignora erro se já existir)
    if (mkfifo(PIPE_NAME, 0666) == -1 && errno != EEXIST) {
        perror("Erro ao criar pipe");
        return 1;
    }

    // Abrir pipe em modo leitura e escrita
    fd = open(PIPE_NAME, O_RDWR);
    if (fd == -1) {
        perror("Erro ao abrir pipe");
        return 1;
    }

    pthread_t pool[THREAD_POOL_SIZE];

    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&pool[i], NULL, worker, NULL);
    }

    printf("Servidor com thread pool iniciado...\n");

    while (1) {
        int bytes = read(fd, buffer, sizeof(buffer) - 1);

        if (bytes > 0) {
            buffer[bytes] = '\0';

            pthread_mutex_lock(&fila_mutex);

            int proximo = (fim + 1) % QUEUE_SIZE;

            if (proximo == inicio) {
                printf("Fila cheia! Requisição descartada.\n");
            } else {
                strcpy(fila[fim], buffer);
                fim = proximo;
                pthread_cond_signal(&cond);
            }

            pthread_mutex_unlock(&fila_mutex);
        }
    }

    close(fd);
    unlink(PIPE_NAME);

    return 0;
}