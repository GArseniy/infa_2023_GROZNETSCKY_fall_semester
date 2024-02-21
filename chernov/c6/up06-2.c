/*
 Напишите функцию:
 void normalize_path(char *buf);

 Функция принимает на вход строку абсолютного пути. Строка всегда начинается с символа '/', в строке не встречаются
 несколько символов '/' подряд.

 Если входная строка не равна "/" и оканчивается на '/', то этот символ с конца должен быть удален.

 В строке-пути должны быть удалены все вхождения каталогов . и .. исходя из того, что каталог . — это переход на текущий каталог,
 а каталог .. — это переход на родительский каталог.

 Функция модифицирует область памяти, в которой находится входная строка. Функция должна обрабатывать пути произвольной длины,
 не обязательно ограниченной константой PATH_MAX.
*/

int is_root(char *buf) {
    if (buf[0] == '/' && buf[1] == '\0') {
        return 1;
    }

    return 0;
}

void delete_i(char *buf, int i) {
    int shift = i;
    while (*(buf + shift) != '\0') {
        *(buf + shift) = *(buf + shift + 1);
        shift++;
    }
}

void normalize_path(char *buf) {
    if (is_root(buf)) {
        return;
    }

    int shift = 1;
    while (*(buf + shift) != '\0') {
        if (shift == 0 || *(buf + shift - 1) != '/') {
            shift++;
            continue;
        }

        if (*(buf + shift) != '\0' && *(buf + shift + 1) != '\0') {
            if (*(buf + shift) == '.' && *(buf + shift + 1) == '/') {
                delete_i(buf, shift);
                delete_i(buf, shift);
                shift--;
            } else if   (*(buf + shift) == '.' && *(buf + shift + 1) == '.' && \
                        (*(buf + shift + 2) == '/' || *(buf + shift + 2) == '\0'))
            {

                delete_i(buf, shift);
                delete_i(buf, shift);
                delete_i(buf, shift);

                shift--;
                if (shift == 0) {
                    continue;
                }

                delete_i(buf, shift);
                shift--;
                while (*(buf + shift) != '/') {
                    delete_i(buf, shift--);
                }
            }
        } else if (*(buf + shift) == '.' && *(buf + shift + 1) == '\0') {
            delete_i(buf, shift);
            shift--;
        }

        shift++;
    }

    if (!is_root(buf) && *(buf + shift - 1) == '/') {
        delete_i(buf, shift - 1);
    }
}
