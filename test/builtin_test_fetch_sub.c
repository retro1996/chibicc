#include "test.h"
#include <stdint.h>

int main(void) {
    int x;
    int r1, r2, r3;

    x = 50;

    // 1) GCC internal builtin (implicit seq-cst, return OLD)
    r1 = __builtin_atomic_fetch_sub(&x, 7);
    // expected:
    //   r1 = 50
    //   x  = 43

    // 2) GNU atomic API: fetch-then-sub (return OLD)
    r2 = __atomic_fetch_sub(&x, 8, __ATOMIC_SEQ_CST);
    // expected:
    //   r2 = 43
    //   x  = 35

    // 3) GNU atomic API: sub-then-fetch (return NEW)
    r3 = __atomic_sub_fetch(&x, 9, __ATOMIC_SEQ_CST);
    // expected:
    //   r3 = 26
    //   x  = 26

    printf("r1=%d r2=%d r3=%d x=%d\n", r1, r2, r3, x);

    // Hard semantic validation
    if (r1 != 50) return 1;
    if (r2 != 43) return 2;
    if (r3 != 26) return 3;
    if (x  != 26) return 4;
    ASSERT(50, r1);
    ASSERT(43, r2);
    ASSERT(26, r3);
    ASSERT(26, x);

    puts("OK");
    return 0;
}
