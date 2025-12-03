#include "test.h"


typedef long long v2di __attribute__((vector_size(16)));

int main() {
    v2di M, V;

    // Case that returns 1
    M = (v2di){0x0FLL, 0x00LL};
    V = (v2di){0x03LL, 0x00LL};
    int r1 = __builtin_ia32_ptestnzc128(V, M);
    ASSERT(1, r1);

    // Case that returns 0 (V covers all bits of M)
    M = (v2di){0x0FLL, 0x00LL};
    V = (v2di){0x0FLL, 0x00LL};
    int r2 = __builtin_ia32_ptestnzc128(V, M);
    ASSERT(0, r2);

    // Case that returns 0 (V has no bits of M set)
    M = (v2di){0x0FLL, 0x00LL};
    V = (v2di){0x00LL, 0x00LL};
    int r3 = __builtin_ia32_ptestnzc128(V, M);
    ASSERT(0, r3);

    printf("ptestnzc128 OK\n");
    return 0;
}
