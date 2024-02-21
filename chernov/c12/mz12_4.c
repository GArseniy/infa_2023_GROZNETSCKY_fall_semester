#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

enum
{
    UMASK = 0700,
};

int main(int argc, char **argv) {
    char *path = getenv("XDG_RUNTIME_DIR");
    if (!path) {
        path = getenv("TMPDIR");
        if (!path) {
            path = "/tmp";
        }
    }

    time_t tm = time(NULL);
    pid_t pid = getpid();

    char path_bash[PATH_MAX + 1] = {};
    snprintf(path_bash, PATH_MAX, "%s/%ld%d", path, tm, pid);

    int fd = open(path_bash, O_WRONLY | O_CREAT | O_TRUNC, UMASK);
    if (fd < 0) {
        fprintf(stderr, "Failed to create file %s\n", path_bash);

        _exit(1);
    }

    char buf[] =    "#!/usr/bin/python3\n"\
                    "import os\n"\
                    "import sys\n"\
                    "sys.set_int_max_str_digits(10**6)\n"\
                    "print(1";

    if (dprintf(fd, "%s", buf) < 0) {
        fprintf(stderr, "Failed to write in %s\n", path_bash);
        unlink(path_bash);

        _exit(1);
    }

    for (int i = 1; i < argc; i++) {
        if (dprintf(fd, "*%s", argv[i]) < 0) {
            fprintf(stderr, "Failed to write in %s\n", path_bash);
            unlink(path_bash);

            _exit(1);
        }
    }

    if (dprintf(fd, ")\nos.remove('%s')", path_bash) < 0) {
        fprintf(stderr, "Failed to write in %s\n", path_bash);
        unlink(path_bash);

        _exit(1);
    }

    close(fd);

    execl(path_bash, path_bash, NULL);

    fprintf(stderr, "Failed to run %s\n", path_bash);
    unlink(path_bash);

    _exit(1);
}
