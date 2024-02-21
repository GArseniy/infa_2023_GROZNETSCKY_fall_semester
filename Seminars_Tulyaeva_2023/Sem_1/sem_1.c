#include "stdio.h"
#include "string.h"
#include "ctype.h"

void my_strcpy(char *s1, const char *s2) {
    while ((*s1++ = *s2++));
}

int my_strcmp(const char *s1, const char *s2) {
    while ((*s1 == *s2) && (*s1)) {
        s1++;
        s2++;
    }
    return (int) (*(unsigned *) s1 - *(unsigned *) s2);
}

const int PATH_MAX = 260;

int main(void) {
    char name[PATH_MAX];
    if (!fgets(name, PATH_MAX, stdin)) {
        return 1;
    }

    if (strlen(name) && (name[strlen(name) - 1] == '\n')) {
        name[strlen(name) - 1] = '\0';
    }

    printf("%s", name);

    FILE *fp;
    if ((fp = fopen(name, "r")) == NULL) { return 2; }

    int stat[27] = {};

    int c;
    while ((c = fgetc(fp)) != EOF) {
        stat[isalpha(c) ? 0 : 'z' - tolower(c)]++;
    }

    fclose(fp);
    for (int i = 1; i < 27; ++i) {
        printf("%d\n", stat[i]);
    }
    return 0;
}
