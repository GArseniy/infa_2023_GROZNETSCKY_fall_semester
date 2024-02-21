#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int
main(void)
{
    for (int x, is_p = 0; scanf("%d", &x) == 1; is_p = 1) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("-1\n");
            fflush(stdout);
            _exit(is_p);
        }
        if (pid > 0) {
            int status;
            wait(&status);
            if (!WIFEXITED(status) || WEXITSTATUS(status)) {
                _exit(is_p);
            }
            printf("%d\n", x);
            fflush(stdout);
            _exit(0);
        }
    }

    return 0;
}