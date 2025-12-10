#include "test.h"
#include <stdint.h>

typedef short s16;
typedef long long s64;
typedef s16 v8hi __attribute__((vector_size(16))); // 8 × 16-bit
typedef s64 v2di __attribute__((vector_size(16))); // 2 × 64-bit

v2di __builtin_ia32_pmovzxwq128(v8hi x);

int main() {
    v8hi a = {1, -2, 3, -4, 5, 6, 7, 8};
    v2di r = __builtin_ia32_pmovzxwq128(a);
    for(int i=0;i<2;i++) printf("%lld ", r[i]);
    printf("\n");
    ASSERT(1, r[0]);
    ASSERT(65534, r[1]);
    printf("pmovzxwq128 OK\n");
    return 0;
}
