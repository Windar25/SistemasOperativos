#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    int i,status;
    pid_t child,father;
    father =  getpid();
    for(i=1;i<4;++i){
        if((child=fork()))break;
    }
    fprintf(stderr,"Es la vuelta nro %d\n",i);
    fprintf(stderr,"Recibi de fork el valor de %d\n",child);
    fprintf(stderr,"Soy el proceso %d con padre %d\n\n",getpid(),getppid());
    char cmd[200];
    if(child==0){
        sprintf(cmd, "pstree -s %d > chain_.txt", getpid());
        system(cmd);
    }
    wait(&status);
}