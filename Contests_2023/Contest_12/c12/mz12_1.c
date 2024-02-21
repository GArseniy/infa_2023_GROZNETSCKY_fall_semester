#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>

enum
{
    ERR_STATUS = 42
};

int main(int argc, char **argv) {
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    }
    
    if (pid == 0) {
        int fd = open(argv[2], O_RDONLY | O_CLOEXEC);
        if (fd < 0) {
            _exit(ERR_STATUS);
        }
        if (dup2(fd, 0) < 0) {
            _exit(ERR_STATUS);
        }
        
        fd = open(argv[3], O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0660);
        if (fd < 0) {
            _exit(ERR_STATUS);
        }
        if (dup2(fd, 1) < 0) {
            _exit(ERR_STATUS);
        }
        
        fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0660);
        if (fd < 0) {
            _exit(ERR_STATUS);
        }
        if (dup2(fd, 2) < 0) {
            _exit(ERR_STATUS);
        }
        
        execlp(argv[1], argv[1], NULL);
        _exit(ERR_STATUS);
    }
    
    int status;
    wait(&status);
    
    printf("%d\n", status);
    
    return 0;
}
