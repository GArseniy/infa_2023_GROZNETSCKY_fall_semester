#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct file
{
    __dev_t st_dev;
    __ino_t st_ino;
    char *path;
} file;

void
init_file(file *f, __dev_t st_dev, __ino_t st_ino, char *path)
{
    f->path = path;
    f->st_ino = st_ino;
    f->st_dev = st_dev;
}

int
compare_files(const void *v1, const void *v2)
{
    file f1 = *(file *) v1;
    file f2 = *(file *) v2;

    if (f1.st_dev != f2.st_dev) {
        return (f1.st_dev > f2.st_dev) ? -1 : 1;
    }
    if (f1.st_ino != f2.st_ino) {
        return (f1.st_ino > f2.st_ino) ? -1 : 1;
    }
    if (f1.path == NULL && f2.path == NULL) {
        return 0;
    }
    if (f1.path == NULL) {
        return -1;
    }
    if (f2.path == NULL) {
        return 1;
    }
    return strcmp(f2.path, f1.path);
}

int
compare_path(const void *v1, const void *v2)
{
    file f1 = *(file *) v1;
    file f2 = *(file *) v2;
    if (f1.path == NULL && f2.path == NULL) {
        return 0;
    }
    if (f1.path == NULL) {
        return 1;
    }
    if (f2.path == NULL) {
        return -1;
    }
    return strcmp(f1.path, f2.path);
}

int
main(int argc, char **argv)
{
    if (argc == 1) {
        return 0;
    }
    file *files = calloc(argc - 1, sizeof(file));
    for (int i = 1; i < argc; ++i) {
        struct stat buf;
        if (stat(argv[i], &buf) < 0) {
            init_file(&files[i - 1], 0, 0, NULL);
            continue;
        }
        init_file(&files[i - 1], buf.st_dev, buf.st_ino, argv[i]);
    }
    qsort(files, argc - 1, sizeof(file), compare_files);

    __dev_t prev_st_dev = files[0].st_dev;
    __ino_t prev_st_ino = files[0].st_ino;
    for (int i = 1; (i < (argc - 1)) && (files[i].path != NULL); ++i) {
        if ((prev_st_dev == files[i].st_dev) && (prev_st_ino == files[i].st_ino)) {
            init_file(&files[i], 0, 0, NULL);
            continue;
        }
        prev_st_dev = files[i].st_dev;
        prev_st_ino = files[i].st_ino;
    }

    qsort(files, argc - 1, sizeof(file), compare_path);
    for (int i = 0; (i < (argc - 1)) && (files[i].path != NULL); ++i) {
        printf("%s\n", files[i].path);
    }

    free(files);
    return 0;
}