#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>

int main(int n, char *argv[]){
    int j,nf;
    pid_t id;
    id=getpid();
    nf = atoi(argv[1]);

    for(j=0;j<nf;j++){
        fork();
    }
    if(getpid()==id){
        char cmd[100];
        sprintf(cmd,"pstree -p %d",id);
        system(cmd);
    }else{
        pause();
    }
    return 0;
}