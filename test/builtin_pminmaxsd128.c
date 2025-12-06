#include "test.h"
#include <stdint.h>

typedef int32_t s32;
typedef s32 v4si __attribute__((vector_size(16))); // 4 x 32-bit signed

// Prototypes for the builtins
v4si __builtin_ia32_pminsd128(v4si x, v4si y);
v4si __builtin_ia32_pmaxsd128(v4si x, v4si y);

int main() {
    v4si a = {1000, -2000, 3000, -4000};
    v4si b = {1500, -2500, 2500, -3500};

    // Call the builtins
    v4si min_res = __builtin_ia32_pminsd128(a, b);
    v4si max_res = __builtin_ia32_pmaxsd128(a, b);

    printf("pminsd128 result: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", (int)min_res[i]);
    }
    printf("\n");

    printf("pmaxsd128 result: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", (int)max_res[i]);
    }
    printf("\n");

    // Expected results
    s32 expected_min[4] = {1000, -2500, 2500, -4000};
    s32 expected_max[4] = {1500, -2000, 3000, -3500};

    for (int i = 0; i < 4; i++) {
        if (min_res[i] != expected_min[i]) {
            printf("pminsd128 FAIL at index %d: got %d, expected %d\n", i, (int)min_res[i], expected_min[i]);
            return 1;
        }
        if (max_res[i] != expected_max[i]) {
            printf("pmaxsd128 FAIL at index %d: got %d, expected %d\n", i, (int)max_res[i], expected_max[i]);
            return 1;
        }
    }

    printf("pminsd128 and pmaxsd128 OK\n");
    return 0;
}
