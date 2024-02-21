#include <stddef.h>
#include <stdbool.h>
#include <bits/stdint-uintn.h>

struct ReadContext
{
    uint8_t *buf;
    size_t size;
    size_t pos;
    uint64_t value_u64;
};

size_t
uleb128_len(uint64_t value)
{
    size_t len = 1;
    while (value >>= 7) {
        ++len;
    }
    return len;
}

uint8_t *
uleb128_encode(uint8_t *ptr, uint64_t value) // FIXME
{
    uint8_t byte = value & ~(1 << 7);
    byte |= (1 << 7) * value;
    *ptr = byte;
    ++ptr;

    while (value >>= 7) {
        byte = value & ~(1 << 7);
        byte |= (1 << 7) * value;
        *ptr = byte;
        ++ptr;
    }

    return ptr;
}

bool
uleb128_decode(struct ReadContext *cntx)
{
    size_t save = cntx->pos;

    uint64_t value = 0;
    int offset = 0;
    uint64_t byte;
    do {
        if (cntx->pos >= cntx->size) {
            cntx->pos = save;
            return false;
        }

        byte = cntx->buf[cntx->pos];
        value |= (byte & ~(1 << 7)) << (offset * 7);
        offset += 7;
        if (offset > 10 || (offset == 10 && (byte != 1))) {
            cntx->pos = save;
            return false;
        }
        ++cntx->pos;
    } while ((byte & (1 << 7)));

    if (!byte && offset != 1) {
        cntx->pos = save;
        return false;
    }

    cntx->pos += offset;
    cntx->value_u64 = value;

    return true;
}