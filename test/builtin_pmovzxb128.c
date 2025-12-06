#include "test.h"
#include <stdint.h>

// Vector types
typedef char s8;
typedef short s16;
typedef s8 v16qi __attribute__((vector_size(16)));  // 16 × 8-bit signed
typedef s16 v8hi __attribute__((vector_size(16)));  // 8 × 16-bit signed


int main() {
    // Input vector: lowest 8 bytes will be zero-extended
    v16qi a = {1, -2, 3, -4, 5, -6, 7, -8, 9, 10, 11, 12, 13, 14, 15, 16};
    v8hi r = __builtin_ia32_pmovzxbw128(a);

    printf("Result: ");
    for (int i = 0; i < 8; i++)
        printf("%d ", r[i]);
    printf("\n");

    // Expected: 1 254 3 252 5 250 7 248 (zero-extended lowest 8 bytes)
    int expected[] = {1, 254, 3, 252, 5, 250, 7, 248};
    for (int i = 0; i < 8; i++) {
        if (r[i] != expected[i]) {
            printf("pmovzxbw128 FAIL\n");
            return 1;
        }
    }
    ASSERT(1, r[0]);
    ASSERT(254, r[1]);
    ASSERT(3, r[2]);
    ASSERT(252, r[3]);
    ASSERT(5, r[4]);
    ASSERT(250, r[5]);
    ASSERT(7, r[6]);
    ASSERT(248, r[7]);
    printf("pmovzxbw128 OK\n");
    return 0;
}
