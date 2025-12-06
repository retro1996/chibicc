#include "test.h"
#include <stdint.h>

// Vector types
typedef char s8;
typedef int s32;
typedef s8 v16qi __attribute__((vector_size(16)));  // 16 × 8-bit signed
typedef s32 v4si __attribute__((vector_size(16)));  // 4 × 32-bit signed



int main() {
    // Input vector: lowest 4 bytes will be zero-extended
    v16qi a = {1, -2, 3, -4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    v4si r = __builtin_ia32_pmovzxbd128(a);

    printf("Result: ");
    for (int i = 0; i < 4; i++)
        printf("%d ", r[i]);
    printf("\n");

    // Expected: 1 254 3 252 (since -2 → 0xFE, -4 → 0xFC zero-extended)
    int expected[] = {1, 254, 3, 252};
    for (int i = 0; i < 4; i++) {
        if (r[i] != expected[i]) {
            printf("pmovzxbd128 FAIL\n");
            return 1;
        }
    }
    ASSERT(1, r[0]);
    ASSERT(254, r[1]);
    ASSERT(3, r[2]);
    ASSERT(252, r[3]);
    printf("pmovzxbd128 OK\n");
    return 0;
}
