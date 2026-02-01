#include "test.h"
#include <stdint.h>

int main(void) {
    unsigned int x;
    unsigned int r1, r2, r3;

    x = 0x0F;   // 0000 1111

    // 1) GCC internal builtin (implicit seq-cst, return OLD)
    r1 = __builtin_atomic_fetch_or(&x, 0x30);
    // x = 0x3F (0011 1111)

    // 2) GNU atomic API: fetch-then-or (return OLD)
    r2 = __atomic_fetch_or(&x, 0x40, __ATOMIC_SEQ_CST);
    // x = 0x7F (0111 1111)

    // 3) GNU atomic API: or-then-fetch (return NEW)
    r3 = __atomic_or_fetch(&x, 0x80, __ATOMIC_SEQ_CST);
    // x = 0xFF (1111 1111)

    printf("r1=0x%X r2=0x%X r3=0x%X x=0x%X\n", r1, r2, r3, x);

    // Hard semantic validation
    if (r1 != 0x0F) return 1;
    if (r2 != 0x3F) return 2;
    if (r3 != 0xFF) return 3;
    if (x  != 0xFF) return 4;
    ASSERT(0x0F, r1);
    ASSERT(0x3F, r2);
    ASSERT(0xFF, r3);
    ASSERT(0xFF, x);

    puts("OK");
    return 0;
}
