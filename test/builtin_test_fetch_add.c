#include "test.h"
#include <stdint.h>

int main(void) {
    int x;
    int r1, r2, r3;

    x = 10;

    // 1) GCC internal builtin (implicit seq-cst, return OLD)
    r1 = __builtin_atomic_fetch_add(&x, 3);
    // expected:
    //   r1 = 10
    //   x  = 13

    // 2) GNU atomic API: fetch-then-add (return OLD)
    r2 = __atomic_fetch_add(&x, 4, __ATOMIC_SEQ_CST);
    // expected:
    //   r2 = 13
    //   x  = 17

    // 3) GNU atomic API: add-then-fetch (return NEW)
    r3 = __atomic_add_fetch(&x, 5, __ATOMIC_SEQ_CST);
    // expected:
    //   r3 = 22
    //   x  = 22

    printf("r1=%d r2=%d r3=%d x=%d\n", r1, r2, r3, x);

    // Hard failure if any semantic is wrong
    if (r1 != 10) return 1;
    if (r2 != 13) return 2;
    if (r3 != 22) return 3;
    if (x  != 22) return 4;
    ASSERT(10, r1);
    ASSERT(13, r2);
    ASSERT(22, r3);
    ASSERT(22, x);

    puts("OK");
    return 0;
}
