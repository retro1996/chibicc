#include "test.h"
#include <stdint.h>

typedef uint32_t u32;
typedef int32_t i32;
typedef u32 v4su __attribute__((vector_size(16))); // 4 x 32-bit unsigned
typedef i32 v4si __attribute__((vector_size(16))); // 4 x 32-bit signed


int main() {
    v4si a = {1000, 2000, 3000, 4000};
    v4si b = {1500, 1500, 3500, 3500};

    // Call the builtins
    v4si min_res = __builtin_ia32_pminud128(a, b);
    v4si max_res = __builtin_ia32_pmaxud128(a, b);

    printf("pminud128 result: ");
    for (int i = 0; i < 4; i++) {
        printf("%u ", (unsigned)min_res[i]);
    }
    printf("\n");

    printf("pmaxud128 result: ");
    for (int i = 0; i < 4; i++) {
        printf("%u ", (unsigned)max_res[i]);
    }
    printf("\n");

    // Expected results
    u32 expected_min[4] = {1000, 1500, 3000, 3500};
    u32 expected_max[4] = {1500, 2000, 3500, 4000};

    for (int i = 0; i < 4; i++) {
        if (min_res[i] != expected_min[i]) {
            printf("pminud128 FAIL at index %d: got %u, expected %u\n", i, min_res[i], expected_min[i]);
            return 1;
        }
        if (max_res[i] != expected_max[i]) {
            printf("pmaxud128 FAIL at index %d: got %u, expected %u\n", i, max_res[i], expected_max[i]);
            return 1;
        }
    }

    printf("pminud128 and pmaxud128 OK\n");
    return 0;
}
