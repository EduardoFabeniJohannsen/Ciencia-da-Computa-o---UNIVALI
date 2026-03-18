#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t id_processo;

    id_processo = fork(); // 2 processos
    id_processo = fork(); // 4 processos
    id_processo = fork(); // 8 processos


    printf("Sou o PID: %d e meu pai eh %d\n", getpid(), getppid());

    return 0;
}