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

    fd = open(PIPE_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Erro ao abrir pipe");
        return 1;
    }

    while (1) {
        printf("\nDigite comando (ou sair): ");
        fgets(buffer, MAX_BUFFER, stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "sair") == 0)
            break;

        write(fd, buffer, strlen(buffer) + 1);
    }

    close(fd);
    return 0;
}