#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define n 3

int main(void){
    int fd[2],i=0,p;
    struct stat sb;

    pipe(fd);
    dup2(fd[0],0);
    dup2(fd[1],1);
    close(fd[0]);
    close(fd[1]);
    while(i<n){
        pipe(fd);
        p=fork();
        p ? dup2(fd[1],1) : dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        if(p)break;
        i++;
    }
    while(waitpid(-1,NULL,-1)!=-1);
    fprintf(stderr,"Process %d. inodes: ",getpid());
    fstat(0,&sb);
    fprintf(stderr,"0(%ld), : ",sb.st_ino);
    fstat(1,&sb);
    fprintf(stderr,"1(%ld)\n",sb.st_ino);
    exit(0);
}