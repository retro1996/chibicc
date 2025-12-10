#include "test.h"
#include <stdint.h>

// Vector types
typedef int s32;
typedef long long s64;
typedef s32 v4si __attribute__((vector_size(16)));   // 4 × 32-bit signed
typedef s64 v2di __attribute__((vector_size(16)));   // 2 × 64-bit signed



int main() {
    // Input vector: lowest 2 elements will be sign-extended
    v4si a = {100, -200, 300, -400};
    v2di r = __builtin_ia32_pmovsxdq128(a);

    printf("Result: ");
    for (int i = 0; i < 2; i++)
        printf("%lld ", (long long)r[i]);
    printf("\n");

    // Expected: 100 -200
    if (r[0] != 100 || r[1] != -200) {
        printf("pmovsxdq128 FAIL\n");
        return 1;
    }
    ASSERT(100, r[0]);
    ASSERT(-200, r[1]);
    printf("pmovsxdq128 OK\n");
    return 0;
}
