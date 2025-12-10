#include "test.h"

typedef int v4si __attribute__((vector_size(16)));

int main() {
    // Pairwise subtract 32-bit:
    // [a0-a1, a2-a3, b0-b1, b2-b3]

    v4si a = {10, 2, 100, 30};
    v4si b = {50, 5, 300, 100};

    v4si r = __builtin_ia32_phsubd128(a, b);

    ASSERT(8,     r[0]);   // 10 - 2
    ASSERT(70,    r[1]);   // 100 - 30
    ASSERT(45,    r[2]);   // 50 - 5
    ASSERT(200,   r[3]);   // 300 - 100

    printf("OK\n");
    return 0;
}
