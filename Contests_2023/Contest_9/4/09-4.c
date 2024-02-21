#include <inttypes.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

static char encLookupTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

char *
b64u_encode(const uint8_t *data, size_t size)
{
    if (size == 0) {
        char *res = calloc(1, sizeof(*res));
        return res;
    }
    char *res = calloc(((size - 1) / 3 + 1) * 4 + 1, sizeof(*res));
    size_t len = 0;
    int i = 0;
    int indexOfLastCompleteTriple = (int) (size / 3) * 3;
    for (i = 0; i < indexOfLastCompleteTriple; i += 3) {
        res[len++] = encLookupTable[(data[i] >> 2)];
        res[len++] = encLookupTable[((data[i] & 0x03) << 4) | ((data[i + 1] & 0xF0) >> 4)];
        res[len++] = encLookupTable[((data[i + 1] & 0x0F) << 2) | ((data[i + 2] & 0xC0) >> 6)];
        res[len++] = encLookupTable[data[i + 2] & 0x3F];
    }

    if (i < size) {
        uint8_t idx1 = data[i];
        uint8_t idx2 = (i + 1 < size) ? data[i + 1] : (uint8_t) 0;
        res[len++] = encLookupTable[idx1 >> 2];
        res[len++] = encLookupTable[((idx1 & 0x03) << 4) | ((idx2 & 0xF0) >> 4)];
        if (i + 1 < size) {
            res[len++] = encLookupTable[((idx2 & 0x0F) << 2)];
        }
    }

    return res;
}

bool
b64u_decode(const char *str, uint8_t **p_data, size_t *p_size)
{
    size_t str_size = strlen(str);
    if (str_size == 0) {
        *p_size = 0;
        uint8_t *res = calloc(1, sizeof(*res));
        res[0] = '\0';
        *p_data = res;
        return true;
    }

    char *correctStr = calloc(strlen(str) + 1, sizeof(*correctStr));
    size_t size = 0;

    for (int j = 0; j < str_size; j++) {
        if (!isspace(str[j])) {
            correctStr[size++] = str[j];
        }
    }

    size_t new_size = ((size - 1) / 4 + 1) * 3;
    uint8_t *res = malloc((new_size + 1) * sizeof(*res));

    size_t i = 0;
    size_t outpos = 0;
    while (i < size) {
        if (i >= size) {
            continue;
        }
        char *p1 = strchr(encLookupTable, str[i]);
        if (p1 == NULL) {
            free(correctStr);
            free(res);
            return false;
        }
        i++;
        if (i >= size) {
            continue;
        }
        char *p2 = strchr(encLookupTable, str[i]);
        if (p2 == NULL) {
            free(correctStr);
            free(res);
            return false;
        }
        i++;
        char *p3 = NULL;
        if (i < size) {
            p3 = strchr(encLookupTable, str[i]);
            if (p3 == NULL) {
                free(correctStr);
                free(res);
                return false;
            }
        }
        i++;
        char *p4 = NULL;
        if (i < size) {
            p4 = strchr(encLookupTable, str[i]);
            if (p4 == NULL) {
                free(correctStr);
                free(res);
                return false;
            }
        }
        i++;
        uint8_t s1 = (uint8_t) (p1 - encLookupTable);
        uint8_t s2 = (uint8_t) (p2 - encLookupTable);
        uint8_t s3 = (uint8_t) (p3 - encLookupTable);
        uint8_t s4 = (uint8_t) (p4 - encLookupTable);
        res[outpos] = (s1 << 2) | (s2 >> 4);
        outpos++;
        if (p3 != NULL) {
            res[outpos] = (s2 << 4) | (s3 >> 2);
            outpos++;
        }

        if (p4 != NULL) {
            res[outpos] = (s3 << 6) | s4;
            outpos++;
        }
    }
    res = realloc(res, (outpos + 1) * sizeof(*res));
    res[outpos] = '\0';

    *p_data = res;
    *p_size = outpos;
    free(correctStr);
    return true;
}

int
main(void)
{
    uint8_t str[] = {'1'};
    size_t size = sizeof(str);
    char *coded = b64u_encode(str, size);
    int i = 0;
    while(coded[i] != '\0') {
        printf("%c", coded[i]);
        i++;
    }
    printf("\n");
    uint8_t *res;
    size_t s;
    bool fl = b64u_decode(coded, &res, &s);
    for (int i = 0; i < s; i++) {
        printf("%c", res[i]);
    }

    return 0;
}