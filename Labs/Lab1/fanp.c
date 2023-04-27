#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    int i,status;
    pid_t child,pid_padre;

    pid_padre=getpid();
    for(i=1;i<4;++i){
        if((child=fork())<=0)break;
        else fprintf(stderr,"Este es el ciclo nro %d y se esta creando el proceso %d \n",i,child);
    }
    if(pid_padre==getpid())for(i=1;i<4;++i)wait(&status);
    fprintf(stderr,"Este es el proceso %d con padre %d \n",getpid(),getppid());
    if(child==0 && i==4){
        char cmd[100];
        sprintf(cmd,"pstree -s %d > fanp.txt",getpid());
        system(cmd);
    }
}