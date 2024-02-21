#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int max_cnt;
pid_t target_pid, pid1;
volatile int cnt;
int fd[2];
FILE *fin, *fout;
int status;

void SigHndlr(int s) {
    fscanf(fin, "%d %d", &cnt, &target_pid);
    fflush(fin);

    if (cnt < max_cnt) {
        int flag = target_pid == pid1 ? 2 : 1;

        printf("%d %d\n", flag, cnt);
        fflush(stdout);

        cnt++;

        fprintf(fout, "%d %d\n", cnt, getpid());
        fflush(fout);

        kill(target_pid, SIGUSR1);
    } else {
        kill(target_pid, SIGKILL);
        _exit(0);
    }
}

int main(int argc, char **argv) {
    sscanf(argv[1], "%d", &max_cnt);

    pipe(fd);
    fin = fdopen(fd[0], "r");
    fout = fdopen(fd[1], "w");
    signal(SIGUSR1, SigHndlr);

    cnt = 1;
    
    pid_t pid2;
    
    if ((pid1 = fork()) == 0) {
        fprintf(fout, "%d %d\n", cnt, getpid());
        fflush(fout);

        while (1) {
            pause();
        }

        fclose(fout);
        fclose(fin);
        return 0;
    } 

    if ((pid2 = fork()) == 0) {
        fscanf(fin, "%d %d", &cnt, &target_pid);

        fprintf(fout, "%d %d\n", cnt, getpid());
        fflush(fout);

        kill(target_pid, SIGUSR1);

        while (1) {
            pause();
        }
    }
    
    fclose(fin);
    fclose(fout);
    
    while (wait(NULL) != -1) {}
    printf("Done\n");
}

