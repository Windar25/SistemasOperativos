#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>

int main(int n, char *argv[]){
    int j,nf,paip[2];
    pid_t id;
    id=getpid();
    nf = atoi(argv[1]);

    pipe(paip);

    for(j=0;j<nf;j++){
        fork();
    }
    if(getpid()==id){
        char aux[1000],cmd1[1000];
        for(j=0;j<nf;j++){
            wait(NULL);
            close(paip[1]);
            read(paip[0],aux,1000);
            close(paip[0]);
            sprintf(cmd1,"%s\n",aux);
        }
        char cmd[100];
        sprintf(cmd,"pstree -p %d",id);
        system(cmd);
    }else{
        char cmd1[1000];
        sprintf(cmd1,"Soy el proceso con PID: %d\n",(int)getpid());
        close(paip[0]);
        write(paip[1],cmd1,1000);
        close(paip[1]);
        pause();
    }
    return 0;
}