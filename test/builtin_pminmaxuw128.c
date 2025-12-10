#include "test.h"
#include <stdint.h>
//#include <smmintrin.h>

typedef uint16_t u16;
typedef int16_t i16;
typedef u16 v8hu __attribute__((vector_size(16))); // 8 x 16-bit unsigned
typedef i16 v8hi __attribute__((vector_size(16))); // 8 x 16-bit unsigned

// // Provide prototypes for the builtins so we can test them
// v8hu __builtin_ia32_pminuw128(v8hu x, v8hu y);
// v8hu __builtin_ia32_pmaxuw128(v8hu x, v8hu y);

int main() {
    v8hu a = {100, 200, 300, 400, 500, 600, 700, 800};
    v8hu b = {150, 150, 350, 350, 450, 650, 650, 750};

    // Call the builtins
    v8hu min_res = (v8hu)__builtin_ia32_pminuw128((v8hi)a, (v8hi)b);
    v8hu max_res = (v8hu)__builtin_ia32_pmaxuw128((v8hi)a, (v8hi)b);

    printf("pminuw128 result: ");
    for (int i = 0; i < 8; i++) {
        printf("%u ", (unsigned)min_res[i]);
    }
    printf("\n");

    printf("pmaxuw128 result: ");
    for (int i = 0; i < 8; i++) {
        printf("%u ", (unsigned)max_res[i]);
    }
    printf("\n");

    // Expected results
    u16 expected_min[8] = {100, 150, 300, 350, 450, 600, 650, 750};
    u16 expected_max[8] = {150, 200, 350, 400, 500, 650, 700, 800};

    for (int i = 0; i < 8; i++) {
        if (min_res[i] != expected_min[i]) {
            printf("pminuw128 FAIL at index %d: got %u, expected %u\n", i, min_res[i], expected_min[i]);
            return 1;
        }
        if (max_res[i] != expected_max[i]) {
            printf("pmaxuw128 FAIL at index %d: got %u, expected %u\n", i, max_res[i], expected_max[i]);
            return 1;
        }
    }

    printf("pminuw128 and pmaxuw128 OK\n");
    return 0;
}
