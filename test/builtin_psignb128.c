#include "test.h"
#include <stdio.h>

typedef char v16qi __attribute__((vector_size(16)));

int main() {
    v16qi a = {1,-2,3,-4,5,-6,7,-8, 9,-10,11,-12,13,-14,15,-16};
    v16qi b = {1,1,-1,-1,1,1,-1,-1, 1,1,-1,-1,1,1,-1,-1};

    v16qi r = __builtin_ia32_psignb128(a, b);

    // expected: a[i]*sign(b[i])
    // [1,-2,-3,4,5,-6,-7,8,9,-10,-11,12,13,-14,-15,16]
    int expected[16] = {1,-2,-3,4,5,-6,-7,8,9,-10,-11,12,13,-14,-15,16};

    for (int i=0;i<16;i++)
        ASSERT(expected[i], r[i]);

    printf("PSIGNB128 OK\n");
    return 0;
}
