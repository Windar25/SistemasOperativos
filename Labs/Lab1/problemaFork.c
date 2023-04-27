#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


void print_process_tree(pid_t pid, int depth) {
    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return;
    }
    if (child_pid == 0) {
        // child process
        printf("%*s- %d\n", depth * 4, "", getpid());
        print_process_tree(getpid(), depth + 1);
        _exit(0);
    } else {
        // parent process
        printf("%*s+ %d\n", depth * 4, "", pid);
        print_process_tree(child_pid, depth + 1);
    }
}

int main(int argc, char **argv){
    int x;
    pid_t pid;
    pid = getpid();
    x = fork() + fork();
    if(x==0){
        printf("Yo soy el último hijo con pid: %d\n",getpid());
    }else{
        if(getpid()==pid){
            printf("Yo soy el proceso padre de la raiz con pid: %d \n",getpid());
        }else if(getppid==pid){
            printf("Yo soy el proceso hijo de la raiz con pid: %d  \n",getpid());
        }
    }
    printf("Soy el proceso %d, mi padre es %d\n", getpid(), getppid());
    return 0;
}