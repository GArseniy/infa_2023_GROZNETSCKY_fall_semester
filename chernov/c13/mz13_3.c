#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        if (fork() == 0) {
            int fdin = open(argv[4], O_RDONLY);
            dup2(fdin, 0);
            close(fdin);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
        
        int status;
        wait(&status);
        if (!WIFEXITED(status) || WEXITSTATUS(status)) {
            _exit(0);
        }
        
        if (fork() == 0) {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
        wait(NULL);
        _exit(0);
    }
    
    if (fork() == 0) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        
        int fdout = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0700);
        dup2(fdout, 1);
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }
    close(fd[1]);
    close(fd[0]);
    while(wait(NULL) != -1) {}
    
    return 0;
}
