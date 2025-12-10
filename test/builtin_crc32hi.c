#include "test.h"

typedef unsigned int u32;
typedef unsigned short u16;

int main() {
    u32 crc = 0x12345678;
    u16 v  = 0xBEEF;

    u32 r = __builtin_ia32_crc32hi(crc, v);
    ASSERT(3615629532, r);
    printf("CRC32HI: %u\n", r);
}
