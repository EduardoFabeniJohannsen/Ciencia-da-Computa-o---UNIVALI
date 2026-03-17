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
        fprintf(stderr,"Eu sou o filho\n");
        execlp("/bin/ls","ls",NULL);
    }
    else (pid == 0 ) {
        fprintf(stderr,"Eu sou o pai\n",pid);
        wait(null);
        printg("Filho completo\n");
    }
    return 0;
}