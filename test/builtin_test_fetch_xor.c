#include "test.h"
#include <stdint.h>

int main(void) {
    unsigned int x;
    unsigned int r1, r2, r3;

    x = 0xAA;   // 1010 1010

    // 1) GCC internal builtin (implicit seq-cst, return OLD)
    r1 = __builtin_atomic_fetch_xor(&x, 0xFF);
    // x = 0x55 (0101 0101)

    // 2) GNU atomic API: fetch-then-xor (return OLD)
    r2 = __atomic_fetch_xor(&x, 0x0F, __ATOMIC_SEQ_CST);
    // x = 0x5A (0101 1010)

    // 3) GNU atomic API: xor-then-fetch (return NEW)
    r3 = __atomic_xor_fetch(&x, 0x33, __ATOMIC_SEQ_CST);
    // x = 0x69 (0110 1001)

    printf("r1=0x%X r2=0x%X r3=0x%X x=0x%X\n", r1, r2, r3, x);

    // Hard semantic validation
    if (r1 != 0xAA) return 1;
    if (r2 != 0x55) return 2;
    if (r3 != 0x69) return 3;
    if (x  != 0x69) return 4;
    ASSERT(0xAA, r1);
    ASSERT(0x55, r2);
    ASSERT(0x69, r3);
    ASSERT(0x69, x);

    puts("OK");
    return 0;
}
