#include "test.h"
#include <stdint.h>

int main(void) {
    unsigned int x;
    unsigned int r1, r2, r3;

    x = 0xFF;   // 1111 1111

    // 1) GCC internal builtin (implicit seq-cst, return OLD)
    r1 = __builtin_atomic_fetch_and(&x, 0xF0);
    // x = 0xF0 (1111 0000)

    // 2) GNU atomic API: fetch-then-and (return OLD)
    r2 = __atomic_fetch_and(&x, 0xCC, __ATOMIC_SEQ_CST);
    // x = 0xC0 (1100 0000)

    // 3) GNU atomic API: and-then-fetch (return NEW)
    r3 = __atomic_and_fetch(&x, 0xAA, __ATOMIC_SEQ_CST);
    // x = 0x80 (1000 0000)

    printf("r1=0x%X r2=0x%X r3=0x%X x=0x%X\n", r1, r2, r3, x);

    // Hard semantic validation
    if (r1 != 0xFF) return 1;
    if (r2 != 0xF0) return 2;
    if (r3 != 0x80) return 3;
    if (x  != 0x80) return 4;
    ASSERT(0xFF, r1);
    ASSERT(0xF0, r2);
    ASSERT(0x80, r3);
    ASSERT(0x80, x);

    puts("OK");
    return 0;
}
