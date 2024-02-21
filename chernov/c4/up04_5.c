/*
 В аргументах командной строки задаются имя входного бинарного файла (FILE1), имя выходного бинарного файла (FILE2)
 и положительное 32-битное знаковое целое число (MOD). Файл FILE1 содержит множество положительных целых чисел,
 представленное в виде битового массива. Бит 0 (младший бит первого байта) в файле соответствует числу 1, бит 7
 (старший бит первого байта) в файле соответствует числу 8 и т. д. Установленный бит означает, что соответствующее число
 присутствует во множестве. Для каждого числа x, присутствующего во множестве, хранящемся в FILE1, в бинарный файл FILE2
 запишите 32-битное знаковое целое число $\sum_{i=1}^x i^2 \pmod{MOD}$, то есть остаток от деления на MOD суммы
 квадратов всех чисел от 1 до x включительно. Числа должны быть записаны в порядке возрастания значения x.
 Числа записываются в порядке байт хоста. Для работы с файлами использовать интерфейс системных вызовов.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>
#include <errno.h>

enum
{
    CHAR_SIZE = 8
};

int main(int argc, char **argv) {
    if (argc < 4) {
        return 1;
    }

    int fd_input = open(argv[1], O_RDONLY);
    int fd_output = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd_input < 0 || fd_output < 0) {
        return 1;
    }

    int MOD;
    sscanf(argv[3], "%d", &MOD);

    unsigned char buf;
    int cur = 1;
    while (read(fd_input, &buf, sizeof(buf)) == sizeof(buf)) {
        for (int i = 0; i < CHAR_SIZE; i++) {
            if (buf & 0x1) {
                unsigned long long x = (unsigned long long)cur * (cur + 1) * (2 * cur + 1) / 6;
                x %= MOD;

                unsigned int tmp = (unsigned int)x;

                if (write(fd_output, &tmp, sizeof(tmp)) != sizeof(tmp)) {
                    return 1;
                }
            }

            buf >>= 1;
            cur++;
        }
    }

    if (close(fd_input) < 0 || close(fd_output) < 0) {
        return 0;
    }
}
