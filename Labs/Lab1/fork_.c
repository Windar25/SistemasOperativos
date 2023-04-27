#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(void){
    int status;
    pid_t child;
    if((child=fork())){
        fprintf(stderr,"Fork devolvio %d por tanto soy el padre con ID = %d\n",child,getpid());
    }else{
        fprintf(stderr,"Fork devolvio %d por tanto soy el hijo con ID = %d\n",child,getpid());
        char cadena[100];
        sprintf(cadena, "pstree -s %d > /home/gabo52/aprocesos.txt\n", getpid());
        printf(cadena);
        system(cadena);
    }
    wait(&status);
    return 0;
}

