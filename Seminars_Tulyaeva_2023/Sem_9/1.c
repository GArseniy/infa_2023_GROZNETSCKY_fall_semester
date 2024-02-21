#include <unistd.h>

int
main(int argc, char **argv)
{
    char *m[] = {"ls", "-al", NULL};
    execvp("ls", m); // execlp("ls", "ls", "-al", NULL);
    return 0;
}
