#include "test.h"
#include <stdint.h>

typedef char s8;
typedef long long s64;
typedef s8 v16qi __attribute__((vector_size(16))); // 16 × 8-bit
typedef s64 v8di __attribute__((vector_size(16))); // 2 × 64-bit


int main() {
    v16qi a = {1, -2, 3, -4, 5, -6, 7, -8, 9, 10, 11, 12, 13, 14, 15, 16};
    v8di r = __builtin_ia32_pmovzxbq128(a);
    for(int i=0;i<8;i++) printf("%lld ", r[i]);
    printf("\n");
    ASSERT(1, r[0]);
    ASSERT(254, r[1]);

    printf("pmovzxbq128 OK\n");
    printf("\n");
    return 0;
}
