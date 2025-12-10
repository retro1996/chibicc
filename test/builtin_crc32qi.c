#include "test.h"
#include <stdint.h>
#include <smmintrin.h>



int main() {
    unsigned int r1 = __builtin_ia32_crc32qi(0u, 0x00);
    unsigned int r2 = __builtin_ia32_crc32qi(0u, 0xFF);
    unsigned int r3 = __builtin_ia32_crc32qi(0x12345678u, 0xAB);

    printf("r1 = %u\n", r1);     // expected 0x00000000
    printf("r2 = %u\n", r2);     // expected 0x77073096
    printf("r3 = %u\n", r3);     // known CRC32 value

    ASSERT(0, r1);
    ASSERT(2910671697, r2);
    ASSERT(3230737929, r3);
    printf("crc32qi OK\n");
    return 0;
}
