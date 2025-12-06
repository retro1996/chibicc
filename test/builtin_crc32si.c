#include "test.h"

typedef unsigned int u32;

int main() {
    u32 crc = 0;
    u32 v   = 0xDEADBEEF;

    u32 r = __builtin_ia32_crc32si(crc, v);
    ASSERT(161029396, r);
    printf("CRC32SI: %u\n", r);
}
