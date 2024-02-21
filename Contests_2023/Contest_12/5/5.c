#include <unistd.h>
#include <stdio.h>
#include <wait.h>
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

char *
make_code(char *code_2)
{
    const char code_1[] = "#include <stdio.h>\n"
                          "#include <stdlib.h>\n"
                          "\n"
                          "int\n"
                          "main(int argc, char **argv)\n"
                          "{\n"
                          "    int summon = 0;\n"
                          "    int disqualify = 1;\n"
                          "    int reject = 2;\n"
                          "\n"
                          "    int x;\n"
                          "    while(scanf(\"%d\", &x) != -1) {\n"
                          "        int res = ";

    const char code_3[] = ";\n"
                          "        switch (res) {\n"
                          "        case 0:\n"
                          "            printf(\"summon\\n\");\n"
                          "            break;\n"
                          "        case 1:\n"
                          "            printf(\"disqualify\\n\");\n"
                          "            break;\n"
                          "        case 2:\n"
                          "            printf(\"reject\\n\");\n"
                          "            break;\n"
                          "        default:\n"
                          "            break;\n"
                          "        }\n"
                          "    }\n"
                          "    unlink(argv[0]);"
                          "    return 0;\n"
                          "}";

    unsigned code_size = sizeof(code_1) + strlen(code_2) + sizeof(code_3);

    char *code = calloc(code_size, sizeof(*code));
    if (snprintf(code, code_size, "%s%s%s", code_1, code_2, code_3) >= code_size) {
        fprintf(stderr, "C-code writing error\n");
        _exit(1);
    }

    return code;
}

void
gen_name(char *path, char *c_file, char *out_file)
{
    pid_t pid = getpid();
    time_t tm = time(NULL);

    snprintf(c_file, PATH_MAX, "%s/%d%ld.c", path, pid, tm);
    snprintf(out_file, PATH_MAX, "%s/%d%ld.out", path, pid, tm);
}

void
create_c_file(char *c_file, char *code)
{
    int fd;
    if ((fd = creat(c_file, 0600)) < 0 || dprintf(fd, "%s", code) < 0) {
        fprintf(stderr, ".C-file creating error\n");
        unlink(c_file);
        _exit(1);
    }
    close(fd);
}

void
compile_out_file(char *c_file, char *out_file)
{
    if (!fork()) {
        execlp("gcc", "gcc", c_file, "-o", out_file, NULL);
        _exit(1);
    }

    int st;
    wait(&st);
    if (!WIFEXITED(st) || WEXITSTATUS(st)) {
        unlink(c_file);
        unlink(out_file);
        fprintf(stderr, "Compilation error\n");
        _exit(1);
    }
}

int
main(int argc, char **argv)
{
    char *path = get_dir();
    char *code = make_code(argv[1]);

    char c_file[PATH_MAX], out_file[PATH_MAX];
    gen_name(path, c_file, out_file);
    free(path);

    create_c_file(c_file, code);
    free(code);

    compile_out_file(c_file, out_file);
    unlink(c_file);

    execl(out_file, out_file, NULL);
    fprintf(stderr, "Run-time error\n");
    _exit(1);
}