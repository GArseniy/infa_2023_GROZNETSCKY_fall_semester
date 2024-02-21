#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    pid_t pid;
} Node;

enum
{
    OK = 0,
    ERROR = 1
};

Node *
add(Node *head, pid_t pid) {
    Node *tmp = calloc(1, sizeof(Node));
    tmp->next = head;
    tmp->pid = pid;
    return tmp;
}

void
free_list(Node *head, int fl) {
    Node *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        if (fl == ERROR) {
            kill(tmp->pid, SIGKILL);
        }
        free(tmp);
    }
}

int 
main(int argc, char **argv)
{
    Node *proc_list = NULL;
    int status = OK;
    pid_t pid;
    int in = 0;
    int fd[2];
    for (int i = 1; i < argc; ++i) {
        if (i == argc - 1) {
            fd[1] = 1;
        } else if (pipe(fd) < 0) {
            status = ERROR;
            close(in);
            break;
        }
        pid = fork();
        if (pid < 0) {
            status = ERROR;
            close(fd[0]);
            close(fd[1]);
            break;
        }
        if (!pid) {
            dup2(in, 0);
            dup2(fd[1], 1);
            if (i != argc - 1) {
                close(fd[0]);
            }
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        } else {
            if (i != 1) {
                close(in);
            }
            if (i != argc - 1) {
                close(fd[1]);
            }
            proc_list = add(proc_list, pid);
            in = fd[0];
        }
    }
    free_list(proc_list, status);
    while (wait(NULL) > 0){
    }
    _exit(status);
}