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
    UMASK = 0600,
    SHIFT = 100
};

int main(int argc, char **argv) {
    char *path = getenv("XDG_RUNTIME_DIR");
    if (!path) {
        path = getenv("TMPDIR");
        if (!path) {
            path = "/tmp";
        }
    }

    char buf1[] =   "#include <stdio.h>\n"\
                    "#include <stdlib.h>\n"\
                    "int unlink(char *path);\n"\
                    "#define summon printf(\"summon\\n\")\n"\
                    "#define disqualify printf(\"disqualify\\n\")\n"\
                    "#define reject printf(\"reject\\n\")\n"\
                    "int main(int argc, char **argv) {\n"\
                    "\tint x;\n"
                    "\twhile(scanf(\"%d\", &x) != -1) {\n";
    
    int len = sizeof(buf1) + strlen(argv[1]) + SHIFT;
    char *buf = calloc(len, sizeof(*buf));

    snprintf(buf, len, "%s\t\t%s;\n\t}\n\tunlink(argv[0]);\n}\n", buf1, argv[1]);

    char path_c[PATH_MAX + 1] = {};
    char path_out[PATH_MAX + 1] = {};

    time_t tm = time(NULL);
    pid_t pid = getpid();

    snprintf(path_c, PATH_MAX, "%s/%ld%d.c", path, tm, pid);
    snprintf(path_out, PATH_MAX, "%s/%ld%d.out", path, tm, pid);

    int fd = open(path_c, O_WRONLY | O_CREAT | O_TRUNC, UMASK);
    if (fd < 0) {
        fprintf(stderr, "Failed to create file %s\n", path_c);

        _exit(1);
    }

    dprintf(fd, "%s", buf);

    if (fork() == 0) {
        execlp("gcc", "gcc", path_c, "-o", path_out, NULL);
        _exit(1);
    }

    int status;
    wait(&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status)) {
        unlink(path_out);
        unlink(path_c);

        fprintf(stderr, "Failed to compile file %s\n", path_c);

        _exit(1);
    }
    unlink(path_c);
    execl(path_out, path_out, NULL);

    fprintf(stderr, "Failed to run %s\n", path_out);

    _exit(1);
}  
