/*
 Напишите функцию
 int parse_rwx_permissions(const char *str);
 На вход функции подается строка — права доступа к файлу в формате rwx
 (9 знаков). Указатель может принимать значение NULL.

 Функция должна вернуть соответствующее значение прав доступа, либо -1,
 если строка не является корректной записью прав доступа.
 Корректная запись состоит только из символов '-', 'r', 'w', 'x',
 расположенных в правильном порядке. 
*/

#include <string.h>
#include <stdio.h>

int parse_rwx_permissions(const char *str) {
    if (str == NULL) {
        return -1;
    }
    
    char m[] = "rwxrwxrwx";
    char *str1 = m;
    int len = strlen(str);
    unsigned int res = 0, i = 0, flag = 0;
    while (str1 != NULL && i < len) {
        if (str[i] == '-') {
            res <<= 1;
        } else if (*str1 == str[i]) {
            res <<= 1;
            res |= 1;
        } else {
            flag = 1;
            break;
        }
        str1 += sizeof(str1[0]);
        i++;
    }
    
    if (flag || i != len || *str1 != '\0') {
        return -1;
    }
    
    return (int)res;
}

