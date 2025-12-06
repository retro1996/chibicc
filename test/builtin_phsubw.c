#include "test.h"


typedef short v4hi __attribute__((vector_size(8)));

int main() {
    // MMX version: __builtin_ia32_phsubw
    // Operates on 4×16-bit elements, grouping pairs:
    // result = [a0 - a1, a2 - a3, b0 - b1, b2 - b3]

    v4hi a = { 1,  5,  10,  40 };
    v4hi b = { 100, 90,  7,   7 };

    v4hi r = __builtin_ia32_phsubw(a, b);

    // Compute expected:
    // a0 - a1 = 1  - 5  = -4
    // a2 - a3 = 10 - 40 = -30
    // b0 - b1 = 100 - 90 = 10
    // b2 - b3 = 7 - 7 = 0

    ASSERT(-4,  r[0]);
    ASSERT(-30, r[1]);
    ASSERT(10,  r[2]);
    ASSERT(0,   r[3]);

    printf("phsubw (MMX) OK\n");
    return 0;
}
