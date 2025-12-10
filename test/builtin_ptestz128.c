#include "test.h"

typedef long long v2di __attribute__((vector_size(16)));

int main() {
    v2di a = {0x0LL, 0x0LL};
    v2di b = {0x0LL, 0x0LL};
    v2di c = {0xFFLL, 0x0LL};
    v2di d = {0x0LL, 0xFFLL};

    // a & b == 0 -> should return 1
    int r1 = __builtin_ia32_ptestz128(a, b);
    ASSERT(1, r1);

    // c & d == 0 -> should return 1
    int r2 = __builtin_ia32_ptestz128(c, d);
    ASSERT(1, r2);

    // a & c != 0 -> should return 0
    int r3 = __builtin_ia32_ptestz128(a, c);
    ASSERT(1, r3);

    // d & c != 0 -> should return 0
    int r4 = __builtin_ia32_ptestz128(d, c);
    ASSERT(1, r4);

    printf("ptestz128 OK\n");
    return 0;
}
