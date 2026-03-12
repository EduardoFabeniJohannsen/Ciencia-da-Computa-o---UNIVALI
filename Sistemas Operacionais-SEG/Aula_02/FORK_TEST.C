#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t id_processo;

    id_processo = fork();

    if (id_processo == 0) {

        printf("Sou o FILHO\n");
        printf("Meu PID: %d\n", getpid());
        printf("PID do meu pai: %d\n", getppid());
        printf("========\n");

    }

    else if (id_processo > 0) {

        printf("Sou o PAI\n");
        printf("Meu PID: %d\n", getpid());
        printf("PID do meu filho: %d\n", id_processo);

    }

    else {

        printf("Erro ao criar processo\n");

    }

    return 0;
}