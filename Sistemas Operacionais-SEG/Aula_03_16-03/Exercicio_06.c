#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main () {

    pid_t pid;
    pid = fork();

    if (pid == 0 ) {
        printf("Eu sou o filho\n");
    } else {
        printf("Eu sou o pai\n");
    }

    printf("Linha em comun\n");
    return 0;
}