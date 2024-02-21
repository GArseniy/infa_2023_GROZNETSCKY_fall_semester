#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

enum
{
    PORTION = 7,
    FST_BIT = 0x80,
    LAST_BIT = 0x01,
    MAX_SIZE = 10
};

size_t
uleb128_len(uint64_t value)
{
    size_t len = 0;
    do {
        value >>= PORTION;
        ++len;
    } while (value);
    return len;
}

uint8_t *
uleb128_encode(uint8_t *ptr, uint64_t value)
{
    uint8_t tmp;
    do {
        tmp = value & ~FST_BIT;
        value >>= PORTION;
        if (value) {
            tmp |= FST_BIT;
        }
        ptr[0] = tmp;
        ++ptr;
    } while (value);
    return ptr;
}

struct ReadContext
{
    uint8_t *buf;
    size_t size;
    size_t pos;
    uint64_t value_u64;
};

bool
uleb128_decode(struct ReadContext *cntx)
{
    uint64_t value = 0;
    size_t shift = 0;
    uint8_t tmp;
    do {
        if (cntx->pos + shift >= cntx->size) {
            return false;
        }
        tmp = cntx->buf[cntx->pos + shift];
        if (!tmp && shift) {
            return false;
        }
        value |= ((uint64_t) tmp & ~FST_BIT) << (shift * PORTION);
        ++shift;
        if (shift > MAX_SIZE || (shift == MAX_SIZE && (tmp & ~LAST_BIT))) {
            return false;
        }
    } while ((tmp & FST_BIT) != 0);
    cntx->pos += shift;
    cntx->value_u64 = value;
    return true;
}