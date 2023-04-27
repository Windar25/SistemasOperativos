#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DISPLAY1 "PID  INDUK** ** pid (%5.5d) ** ***********\n"
#define DISPLAY2 "PID (%5.5d)  --  ii (%5.5d) ** ***********\n"

int main(void){
    int ii=0;
    pid_t child,id;
    id=getpid();
    printf(DISPLAY1,(int)id);
    if(fork()==0)ii++;
    //waitpid(-1,NULL,0);
    if(fork()==0)ii++; 
    //waitpid(-1,NULL,0);
    if(fork()==0)ii++;
    //waitpid(-1,NULL,0);
    printf(DISPLAY2, getpid(),ii);
    if(getpid()==id){
        char cmd[100];
        sprintf(cmd,"pstree -p %d > isengfork.txt",id);
        system(cmd);
    }else{
        sleep(1);
        waitpid(id,NULL,0);
    }
    return 0;
}