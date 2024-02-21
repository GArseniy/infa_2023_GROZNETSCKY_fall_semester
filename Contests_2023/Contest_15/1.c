#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    int nproc = strtol(argv[1], NULL, 10);
    key_t key = strtol(argv[2], NULL, 10);
    int maxval = strtol(argv[3], NULL, 10);

    int sem = semget(key, nproc, IPC_CREAT | 0666);

    int shm_id = shmget(key, 2 * sizeof(int), IPC_CREAT | 0666);

    int *arr = shmat(shm_id, NULL, 0);

    for (int i = 1; i <= nproc; i++) {
        if (fork() == 0) {
            struct sembuf p = {i - 1, -1, 0};
            while (semop(sem, &p, 1) >= 0) {
                int cur = arr[0];

                printf("%d %d %d\n", i, cur, arr[1]);
                fflush(stdout);

                if (cur == maxval) {
                    semctl(sem, nproc, IPC_RMID, NULL);
                    break;
                }

                cur++;
                // unsigned long long cur_ll = (unsigned)cur;
                // int next = (int)((cur_ll * cur_ll * cur_ll * cur_ll) % nproc);

                int tmp = cur % nproc;
                int next = (tmp * tmp) % nproc;
                next = (next * tmp) % nproc;
                next = (next * tmp) % nproc;

                arr[0] = cur;
                arr[1] = i;

                struct sembuf v = {next, 1, 0};
                semop(sem, &v, 1);
            }

            _exit(0);
        }
    }

    arr[0] = 0;
    arr[1] = 0;

    struct sembuf tmp = {0, 1, 0};
    semop(sem, &tmp, 1);

    while (wait(NULL) != -1) {
    }

    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem, nproc, IPC_RMID, NULL);

    return 0;
}
