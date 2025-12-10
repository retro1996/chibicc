#include "test.h"
#include <stdint.h>

typedef int32_t s32;
typedef long long s64;
typedef s32 v4si __attribute__((vector_size(16)));
typedef s64 v2di __attribute__((vector_size(16)));


int main() {
    v4si a = {1, 2, 3, 4};
    v4si b = {10, 20, 30, 40};

    v2di r = __builtin_ia32_pmuldq128(a, b);

    printf("pmuldq128 result: ");
    for (int i = 0; i < 2; i++) {
        printf("%lld ", (long long)r[i]);
    }
    printf("\n");

    // Expected: 1*10=10, 3*30=90
    if (r[0] != 10 || r[1] != 90) {
        printf("pmuldq128 FAIL\n");
        return 1;
    }
    printf("pmuldq128 OK\n");
    return 0;
}
