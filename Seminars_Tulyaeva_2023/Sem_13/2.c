#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>

int
main(int argc, char **argv)
{
    int nproc = strtol(argv[1], NULL, 0);
    int max = strtol(argv[2], NULL, 0);

    int sem_id = semget(IPC_PRIVATE, nproc, IPC_CREAT | 0666);
    int shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *mem = shmat(shm_id, NULL, 0);

    for (int i = 1; i <= nproc; ++i) {
        if (fork() == 0) {
            struct sembuf p = {(i + 1) % nproc, -1, 0};
            while (semop(sem_id, &p, 1)){

            }

            _exit(0);
        }
    }

    struct sembuf init = {0, 1, 0};
    semop(sem_id, &init, 1);

    while (wait(NULL) != -1) {
    }

    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, nproc, IPC_RMID, NULL);

    return 0;
}
