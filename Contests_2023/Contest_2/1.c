#include "stdio.h"
#include "string.h"


enum
{
    MAX_LEN = 128
};


void get_str(char *s) {
    if (!fgets(s, MAX_LEN, stdin)) {
        s[0] = 0;
        return;
    }

    if (strlen(s) && (s[strlen(s) - 1] == '\n')) {
        s[strlen(s) - 1] = 0;
    }
}


int
main(void)
{
    char s1[MAX_LEN];
    get_str(s1);

    char s2[MAX_LEN];
    get_str(s2);

    char s3[MAX_LEN];
    get_str(s3);

    printf("[Host:%s,Login:%s,Password:%s]\n", s1, s2, s3);
    return 0;
}