#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
#include<signal.h>
#include<time.h>

#define SIZE 5

int main(int n,char *argv[]){
    int sync[2],k;
    char c;

    pipe(sync);
    srand(time(NULL));
    for(k=0;k<2;k++){
        if(!fork()){
            int id,arreglo[SIZE];

            if(!k){
                id = getpid();
                for(k=0;k<SIZE;k++)arreglo[k] = (rand() %101)+200;
                printf("Proceso %d debo tener solo valores pares\n",id);
                for(k=0;k<SIZE;k++)printf("%d %d\n",id,arreglo[k]);
                /*no tocar este write solo de sinconizacion*/
                write(sync[0],&c,sizeof(c));
                exit(0);
            }else{
                id = getpid();
                for(k=0;k<SIZE;k++)arreglo[k]=(rand() % 201)+400;
                /*No tocar este read sirve solo de sincronizacion*/
                read(sync[1],&c,sizeof(c));
                printf("Proceso %d Debo tener solo valores impares\n",id);
                for(k=0;k<SIZE;k++)printf("%d %d\n",id,arreglo[k]);
                exit(0);
                
            }
        }
    }
    wait(NULL);
    wait(NULL);
    return 0;
}