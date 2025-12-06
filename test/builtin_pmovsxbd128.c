#include "test.h"
#include <stdint.h>

typedef char s8;
typedef int s32;
typedef s8 v16qi __attribute__((vector_size(16)));
typedef s32 v4si __attribute__((vector_size(16)));


int main() {
    v16qi a = {1, -2, 3, -4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    v4si r = __builtin_ia32_pmovsxbd128(a);

    printf("Result: ");
    for (int i = 0; i < 4; i++)
        printf("%d ", r[i]);
    printf("\n");

    // Expected: 1 -2 3 -4
    if (r[0] != 1 || r[1] != -2 || r[2] != 3 || r[3] != -4) {
        printf("pmovsxbd128 FAIL\n");
        return 1;
    }
    ASSERT(1, r[0]);
    ASSERT(-2, r[1]);
    ASSERT(3, r[2]);
    ASSERT(-4, r[3]);
    printf("pmovsxbd128 OK\n");
    return 0;
}
