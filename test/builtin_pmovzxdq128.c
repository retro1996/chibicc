#include "test.h"
#include <stdint.h>

typedef int s32;
typedef long long s64;
typedef s32 v4si __attribute__((vector_size(16))); // 4 × 32-bit
typedef s64 v2di __attribute__((vector_size(16))); // 2 × 64-bit

v2di __builtin_ia32_pmovzxdq128(v4si x);

int main() {
    v4si a = {1, -2, 3, -4};
    v2di r = __builtin_ia32_pmovzxdq128(a);
    for(int i=0;i<2;i++) printf("%lld ", r[i]);
    printf("\n");
    ASSERT(1, r[0]);
    ASSERT(18446744073709551614ULL, r[1]);
    printf("pmovzxdq128 OK\n");
    return 0;
}
