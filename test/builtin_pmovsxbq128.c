#include "test.h"
#include <stdint.h>

// Vector types
typedef char s8;
typedef long long s64;
typedef s8 v16qi __attribute__((vector_size(16)));   // 16 × 8-bit signed
typedef s64 v2di __attribute__((vector_size(16)));   // 2 × 64-bit signed


int main() {
    // Input vector: lowest 2 bytes will be sign-extended
    v16qi a = {1, -2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    v2di r = __builtin_ia32_pmovsxbq128(a);

    printf("Result: ");
    for (int i = 0; i < 2; i++)
        printf("%lld ", (long long)r[i]);
    printf("\n");

    // Expected: 1 -2
    if (r[0] != 1 || r[1] != -2) {
        printf("pmovsxbq128 FAIL\n");
        return 1;
    }
    ASSERT(1, r[0]);
    ASSERT(-2, r[1]);
    printf("pmovsxbq128 OK\n");
    return 0;
}
