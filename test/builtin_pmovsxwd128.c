#include "test.h"
#include <stdint.h>

typedef short s16;
typedef int s32;
typedef s16 v8hi __attribute__((vector_size(16)));
typedef s32 v4si __attribute__((vector_size(16)));


int main() {
    v8hi a = {1000, -2000, 3000, -4000, 5000, 6000, 7000, 8000};
    v4si r = __builtin_ia32_pmovsxwd128(a);

    printf("Result: ");
    for (int i = 0; i < 4; i++)
        printf("%d ", r[i]);
    printf("\n");

    // Expected: 1000 -2000 3000 -4000
    if (r[0] != 1000 || r[1] != -2000 || r[2] != 3000 || r[3] != -4000) {
        printf("pmovsxwd128 FAIL\n");
        return 1;
    }
    ASSERT(1000, r[0]);
    ASSERT(-2000, r[1]);
    ASSERT(3000, r[2]);
    ASSERT(-4000, r[3]);
    printf("pmovsxwd128 OK\n");
    return 0;
}
