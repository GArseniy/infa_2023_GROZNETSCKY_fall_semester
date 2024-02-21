#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>

int main(void) {
    int fd[2];
    pipe(fd);
    
    FILE* fin = fdopen(fd[0], "r");
    FILE* fout = fdopen(fd[1], "w");
    
    if (fork() == 0) {
        fclose(fin);
        for (int i = 0; i < 100; i++) {
            fprintf(fout, "%d\n", i);
            fflush(fout);
        }
        _exit(0);
    }
    
    for (int i = 0; i < 100; i++) {
        int k;
        fscanf(fin, "%d", &k);
        printf("%d\n", k);
    }

}
