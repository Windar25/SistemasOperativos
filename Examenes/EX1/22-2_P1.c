#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

void die(char *s);

int main(void){ 
    int i=26, p, a='a';
    FILE *f; struct stat sb;
    if (unlink("f") < 0 && errno != ENOENT) die("unlink error\n");
    while(i-- && (p=fork())) a++;
    while(!p) {
        f = fopen("f", "a");
        fprintf(f, "%c", a);
        fclose(f);
        if (!i) break;
        exit(0);
    }
    if (p) exit(0);
    while(1) {
        stat("f", &sb);
        if (sb.st_size == 26) break;
    }
    execl("/bin/cat", "cat", "f", (char *)0);
    die("exec error\n");
}
void die(char *s)
{ if ( s != (char *) NULL ) { while (*s) (void) write(2, s++, 1); }
    exit( (s == (char *) NULL) ? 0 : 1 );
}