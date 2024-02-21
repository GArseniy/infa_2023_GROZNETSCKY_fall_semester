/*
 В аргументах командной строки передаются 9-битные восьмеричные числа, соответствующие правам доступа к файлам в UNIX.
 Каждый аргумент командной строки содержит только одно число. Незначащие нули у восьмеричного числа в могут отсутствовать, а могут
 и присутствовать. На стандартный поток вывода напечатайте права доступа в rwx-записи. Каждую строку прав доступа выводите
 на отдельной строке текста. 
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

enum
{
    BASE = 8,
    BIT_NUM = 9 
};

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        char *eptr = NULL;
        errno = 0;
        long n = strtol(argv[i], &eptr, BASE);
        if (errno || *eptr || eptr == argv[i] || (int) n != n) {
            continue;
        }

        char m[] = "rwxrwxrwx";
        for (int i = 0; i < BIT_NUM; i++) {
            if (!(n & 1)) {
                m[BIT_NUM - i - 1] = '-';
            }
            
            n >>= 1;
        }

        puts(m);
    }

    return 0;
}
