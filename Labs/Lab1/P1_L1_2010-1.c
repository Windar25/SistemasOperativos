#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    int nprocesos,status;
    int static current_id=1;
    pid_t child;
    if((argc!=2 )|| (nprocesos=atoi(argv[1]))<=0){
        printf("Error, ingrese un número entero\n");
        return 0;
    }
    for(int i=1;i<nprocesos;i++){
        child = fork();
        printf("Soy el proceso %d con pid %d y ppid %d \n",current_id,getpid(),getppid());
        current_id++;
        if(!child){
            child = fork();
            printf("Soy el proceso %d con pid %d y ppid %d \n",current_id,getpid(),getppid());
            current_id++;
            if(!child)break;
            else continue;
        }
    }
    wait(&status);
    wait(&status);
}