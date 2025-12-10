#include "test.h"
#include <stdint.h>

// Vector types
typedef short s16;
typedef long long s64;
typedef s16 v8hi __attribute__((vector_size(16)));   // 8 × 16-bit signed
typedef s64 v2di __attribute__((vector_size(16)));   // 2 × 64-bit signed



int main() {
    // Input vector: lowest 2 words (16-bit) will be sign-extended
    v8hi a = {1000, -2000, 3000, -4000, 5000, 6000, 7000, 8000};
    v2di r = __builtin_ia32_pmovsxwq128(a);

    printf("Result: ");
    for (int i = 0; i < 2; i++)
        printf("%lld ", (long long)r[i]);
    printf("\n");

    // Expected: 1000 -2000
    if (r[0] != 1000 || r[1] != -2000) {
        printf("pmovsxwq128 FAIL\n");
        return 1;
    }
    ASSERT(1000, r[0]);
    ASSERT(-2000, r[1]);
    printf("pmovsxwq128 OK\n");
    return 0;
}
