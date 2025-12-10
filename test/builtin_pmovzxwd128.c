#include "test.h"
#include <stdint.h>

typedef short s16;
typedef int s32;
typedef s16 v8hi __attribute__((vector_size(16))); // 8 × 16-bit
typedef s32 v4si __attribute__((vector_size(16))); // 4 × 32-bit



int main() {
    v8hi a = {1, -2, 3, -4, 5, 6, 7, 8};
    v4si r = __builtin_ia32_pmovzxwd128(a);
    printf("Result: ");
    for(int i=0;i<4;i++) printf("%d ", r[i]);

    ASSERT(1, r[0]);
    ASSERT(65534, r[1]);
    ASSERT(3, r[2]);
    ASSERT(65532, r[3]);
    printf("pmovzxwd128 OK\n");
    printf("\n");

    return 0;
}
