#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, fd_copy;
    fd = open("archivo.txt", O_WRONLY | O_CREAT);
    fd_copy = open("copia.txt", O_WRONLY | O_CREAT);
    dup2(fd, 1);
    dup2(fd_copy, 2);
    printf("Hola, mundo!\n");
    fprintf(stderr, "Este es un mensaje de error.\n");
    close(fd);
    close(fd_copy);
    return 0;
}