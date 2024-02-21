#include <unistd.h>
#include <stdio.h>
#include <sys/file.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

char *
get_dir()
{
    char *path;
    if ((path = getenv("XDG_RUNTIME_DIR"))) {
        return strdup(path);
    }
    if ((path = getenv("TMPDIR"))) {
        return strdup(path);
    }
    return strdup("/tmp");
}

void
gen_name(char *path, char *py_file)
{
    pid_t pid = getpid();
    time_t tm = time(NULL);

    srand(tm);
    int r = rand();

    snprintf(py_file, PATH_MAX, "%s/%d%ld%d.py", path, pid, tm, r);
}

void
make_py_file(char *py_file, int argc, char **argv)
{
    int fd;
    if ((fd = creat(py_file, 0700)) < 0) {
        fprintf(stderr, ".py-file creating error\n");
        _exit(1);
    }

    const char code_1[] = "#!/usr/bin/python3\n"
                          "import os\n"
                          "print(1";
    const char code_2[] = ")\n"
                          "os.remove('";
    const char code_3[] = "')\n";

    if (dprintf(fd, "%s", code_1) < 0) {
        fprintf(stderr, ".py-file writing error\n");
        unlink(py_file);
        _exit(1);
    }

    for (int i = 1; i < argc; i++) {
        if (dprintf(fd, " * %s", argv[i]) < 0) {
            fprintf(stderr, ".py-file writing error\n");
            unlink(py_file);
            _exit(1);
        }
    }

    if (dprintf(fd, "%s%s%s", code_2, py_file, code_3) < 0) {
        fprintf(stderr, ".py-file writing error\n");
        unlink(py_file);
        _exit(1);
    }

    close(fd);
}

int
main(int argc, char **argv)
{
    char *path = get_dir();

    char py_file[PATH_MAX];
    gen_name(path, py_file);
    free(path);

    make_py_file(py_file, argc, argv);

    execl(py_file, py_file, NULL);

    fprintf(stderr, "Run-time error\n");
    unlink(py_file);
    _exit(1);
}