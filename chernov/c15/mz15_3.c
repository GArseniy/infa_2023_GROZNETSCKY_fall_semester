#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>

enum
{
    BASE = 10
};

int mod(int cur, int n) {
    if (cur % n >= 0) {
        return cur % n;
    }
    
    return (cur % n) + n;
}

int main(int argc, char **argv) {
    int n = strtol(argv[1], NULL, BASE);
    int sem = semget(IPC_PRIVATE, n, IPC_CREAT | 0666);
    
    int *a = calloc(n, sizeof(*a));
    semctl(sem, n, SETALL, a);
    free(a);
    setbuf(stdin, 0);

    for (int i = 0; i < n; i++) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            struct sembuf p = {i, -1, 0};
            while (semop(sem, &p, 1) >= 0) {
                int cur;

                if (scanf("%d", &cur) == EOF) {
                    semctl(sem, n, IPC_RMID, NULL);
                    break;
                }

                printf("%d %d\n", i, cur);
                fflush(stdout);
                
                struct sembuf v = {mod(cur, n), 1, 0};
                semop(sem, &v, 1);
            }
            
            _exit(0);
        }
    }
    
    struct sembuf tmp = {0, 1, 0};
    semop(sem, &tmp, 1);
    
    while (wait(NULL) != -1) {}
    
    return 0;
}
