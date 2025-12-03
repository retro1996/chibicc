#include "test.h"
#include <stdio.h>

typedef signed char v16qi __attribute__((vector_size(16)));

int main() {
    v16qi a = {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15
    };

    // Shuffle mask: reverse low 8 bytes, leave high 8 unchanged
    v16qi mask = {
        7,6,5,4,3,2,1,0,
        8,9,10,11,12,13,14,15
    };

    v16qi r = __builtin_ia32_pshufb128(a, mask);

    // Expected:
    ASSERT(7,  r[0]);
    ASSERT(6,  r[1]);
    ASSERT(5,  r[2]);
    ASSERT(4,  r[3]);
    ASSERT(3,  r[4]);
    ASSERT(2,  r[5]);
    ASSERT(1,  r[6]);
    ASSERT(0,  r[7]);
    ASSERT(8,  r[8]);
    ASSERT(9,  r[9]);
    ASSERT(10, r[10]);
    ASSERT(11, r[11]);
    ASSERT(12, r[12]);
    ASSERT(13, r[13]);
    ASSERT(14, r[14]);
    ASSERT(15, r[15]);

    printf("pshufb128 OK\n");
    return 0;
}
