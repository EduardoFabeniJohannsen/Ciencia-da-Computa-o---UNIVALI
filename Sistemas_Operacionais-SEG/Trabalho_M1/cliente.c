#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "banco.h"

int main() {
    int fd;
    char buffer[MAX_BUFFER];

    printf("Cliente iniciado...\n");

    // Abre o pipe para escrita
    fd = open(PIPE_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Erro ao abrir pipe");
        return 1;
    }

    while (1) {
        printf("\nDigite comando (ou sair): ");
        fgets(buffer, MAX_BUFFER, stdin);

        // Remove o \n do final
        buffer[strcspn(buffer, "\n")] = '\0';

        // Condição de saída
        if (strcmp(buffer, "sair") == 0)
            break;

        // Envia para o servidor
        if (write(fd, buffer, strlen(buffer) + 1) == -1) {
            perror("Erro ao escrever no pipe");
            break;
        }
    }

    close(fd);
    return 0;
}