#include <string.h> // It is not extra include. It is for size_t. Do not reject

struct s1
{
    char f1;
    long long f2;
    char f3;
};

struct s2
{
    long long f2;
    char f1;
    char f3;
};

enum
{
    SIZE_OF_S1 = sizeof(struct s1),
    SIZE_OF_S2 = sizeof(struct s2)
};

size_t
compactify(void *ptr, size_t size)
{
    struct s1 *s_ptr1 = (struct s1 *) ptr;
    struct s2 *s_ptr2 = (struct s2 *) ptr;

    for (size_t i = 0; i < size / SIZE_OF_S1; ++i) {
        struct s2 s = {.f1 = s_ptr1[i].f1, .f2 = s_ptr1[i].f2, .f3 = s_ptr1[i].f3};
        s_ptr2[i].f1 = s.f1;
        s_ptr2[i].f2 = s.f2;
        s_ptr2[i].f3 = s.f3;
    }

    return size / SIZE_OF_S1 * SIZE_OF_S2;
}
