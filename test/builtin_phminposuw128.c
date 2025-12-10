#include "test.h"
#include <stdint.h>

typedef uint16_t u16;
typedef int16_t i16;
typedef i16 v8hi __attribute__((vector_size(16)));


int main() {
    v8hi a = {100, 200, 50, 400, 10, 300, 250, 150};
    v8hi r = __builtin_ia32_phminposuw128(a);

    printf("min value = %u, index = %u\n", r[0], r[1]);
    // Expected: min=10, index=4
    if (r[0] != 10 || r[1] != 4) {
        printf("phminposuw128 FAIL\n");
        return 1;
    }
    ASSERT(10, r[0]);
    ASSERT(4, r[1]);
    printf("phminposuw128 OK\n");
    return 0;
}
