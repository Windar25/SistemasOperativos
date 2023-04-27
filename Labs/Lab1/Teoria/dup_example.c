#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, fd_copy;
    fd = open("archivo.txt", O_WRONLY | O_CREAT);
    fd_copy = dup(fd);
    write(fd, "Hola, mundo!\n", 13);
    write(fd_copy, "¡Hola, mundo duplicado!\n", 24);
    close(fd);
    close(fd_copy);
    return 0;
}