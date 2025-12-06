#include "test.h"

typedef unsigned long long u64;

int main() {
    u64 crc = 0;
    u64 v   = 0x1122334455667788ULL;

    u64 r = __builtin_ia32_crc32di(crc, v);
    LASSERT(594666396, r);
    printf("CRC32DI: %llu\n", r);
}
