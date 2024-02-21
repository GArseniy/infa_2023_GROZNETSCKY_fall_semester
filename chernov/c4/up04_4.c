/*
 В аргументах командной строки задается путь к бинарному файлу, содержащему целые знаковые числа типа long long,
 записанные в порядке байт хоста (компьютера, на котором исполняется программа). В файле найдите минимальное число
 и поменяйте его знак. Если минимальное число в файле встречается несколько раз, поменяйте знак только
 у первого по порядку минимального числа. При вычислениях предполагайте неограниченную битность, но в качестве
 результата оставьте младшие 64 бита.

 Для работы с файлом используйте POSIX API. Допускается только один проход по файлу, но бинарный файл является файлом
 произвольного доступа.
*/

#include <sys/file.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        return 1;
    }

    long long shift = 0, min;
    if (read(fd, &min, sizeof(min)) != sizeof(min)) {
        return 0;
    }

    long long cur;
    int i = 1;
    while (read(fd, &cur, sizeof(cur)) == sizeof(cur)) {
        if (cur < min) {
            min = cur;
            shift = i * sizeof(cur);
        }

        i++;
    }

    lseek(fd, shift, SEEK_SET);
    if (min != LLONG_MIN) {
        min = -min;
        if (write(fd, &min, sizeof(min)) != sizeof(min)) {
            return 1;
        }
    }

    if (close(fd) < 0) {
        return 1;
    }

    return 0;
}
