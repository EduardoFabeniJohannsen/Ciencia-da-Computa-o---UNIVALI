#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (){

    pid_t pid;
    pid = fork();

    if (pid < 0 ) {
        fprintf(stderr," Fork deu errado\n");
        return 1;
    }
    else if (pid == 0 ) {
        printf(stderr,"Eu sou o filho\n");
        execlp("/bin/ls","ls",NULL);
    }
    else {
        printf("Eu sou o pai %d\n",pid);
        wait(null);
        printf("Filho completo\n");
    }
    return 0;
}