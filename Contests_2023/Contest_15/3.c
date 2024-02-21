#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    setbuf(stdin, 0);

    int cnt = strtol(argv[1], NULL, 10);
    int sem_arr = semget(IPC_PRIVATE, cnt, IPC_CREAT | 0666);

    int *init = calloc(cnt, sizeof(*init));
    semctl(sem_arr, cnt, SETALL, init);
    free(init);

    for (int i = 0; i < cnt; ++i) {
        if (!fork()) {
            struct sembuf down = {i, -1, 0};
            int buf;
            while (!semop(sem_arr, &down, 1) && scanf("%d", &buf) == 1) {
                printf("%d %d\n", i, buf);
                fflush(stdout);
                struct sembuf up = {buf % cnt + cnt * (buf % cnt < 0), 1, 0};
                semop(sem_arr, &up, 1);
            }
            semctl(sem_arr, cnt, IPC_RMID, NULL);
            _exit(0);
        }
    }

    struct sembuf up = {0, 1, 0};
    semop(sem_arr, &up, 1);

    while (wait(NULL) != -1) {
    }
    return 0;
}