#include "test.h"
#include <stdint.h>

// Optional: memory order constant for __atomic builtins
#ifndef __ATOMIC_SEQ_CST
#define __ATOMIC_SEQ_CST 5
#endif

int main(void) {
    int x, y;

    // -------------------------------
    // __builtin_atomic_fetch_nand
    x = 0xF5;
    int old1 = __builtin_atomic_fetch_nand(&x, 0x0F, __ATOMIC_SEQ_CST);
    printf("__builtin_atomic_fetch_nand: old=%d new=%d\n", old1, x);
    ASSERT(0xF5, old1);
    ASSERT(~(0xF5 & 0x0F), x);

    // -------------------------------
    // __atomic_fetch_nand
    x = 0xF5;
    int old2 = __atomic_fetch_nand(&x, 0x0F, __ATOMIC_SEQ_CST);
    printf("__atomic_fetch_nand: old=%d new=%d\n", old2, x);
    ASSERT(0xF5, old2);
    ASSERT(~(0xF5 & 0x0F), x);

    // -------------------------------
    // __atomic_nand_fetch
    x = 0xF5;
    int new3 = __atomic_nand_fetch(&x, 0x0F, __ATOMIC_SEQ_CST);
    printf("__atomic_nand_fetch: old=%d new=%d\n", ~(new3 & 0xFF), new3); // old = ~new & mask?
    ASSERT(~(0xF5 & 0x0F), new3);
    ASSERT(new3, x);

    // -------------------------------
    // Legacy __sync_fetch_and_nand
    y = 0xF5;
    int old4 = __sync_fetch_and_nand(&y, 0x0F);
    printf("__sync_fetch_and_nand: old=%d new=%d\n", old4, y);
    ASSERT(0xF5, old4);
    ASSERT(~(0xF5 & 0x0F), y);

    return 0;
}
