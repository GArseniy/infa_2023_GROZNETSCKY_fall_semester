// IPC_EXCL —> ret -1
// | 0600 без exe
// semget(..., 0);
// IPC_PRIVATE instead of key for access for only children

// union { int val, ushort *array, struct semid_ds *buf }
// IPC_RMID, GETVAL, SETVAL, GETALL, SETALL, IPC_STAT

// SEM_UNDO instead of 0
// IPC_NOWATE

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int
main(void)
{
    int semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0600);
    int shmid = shmget(IPC_PRIVATE, 256, IPC_CREAT | 0600);
    char *mem = shmat(shmid, NULL, 0);

    if (!fork()) {
        struct sembuf p1 = {1, -1, 0};
        struct sembuf v0 = {0, 1, 0};

        while (fgets(mem, 256, stdin)) {
            semop(semid, &v0, 1);
            semop(semid, &p1, 1);
        }
        semctl(semid, 0, IPC_RMID, 0);
        shmctl(shmid, IPC_RMID, 0);
        _exit(0);
    }

    if (!fork()) {
        struct sembuf p0 = {0, -1, 0};
        struct sembuf v1 = {1, 1, 0};

        while (semop(semid, &p0, 1) >= 0) {
            puts(mem);
            semop(semid, &v1, 1);
        }
        _exit(0);
    }
    while (wait(NULL) != -1) {
    }
    semctl(semid, IPC_RMID, 0);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}