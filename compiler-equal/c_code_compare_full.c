#include <stdint.h>

void helper_func(void);

void cmp_secret64(uint64_t a, uint64_t b) {
    if (a == b)
        helper_func();
}

void cmp_secret32(uint32_t a, uint32_t b) {
    if (a == b)
        helper_func();
}

void cmp_secret16(uint16_t a, uint16_t b) {
    if (a == b)
        helper_func();
}