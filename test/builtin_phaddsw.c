#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {30000, 30000, -30000, -30000};
    v4hi b = {20000, -20000, 20000, -20000};

    v4hi r = __builtin_ia32_phaddsw(a, b);

    // Saturated 16-bit signed:
    // a0+a1 = 30000+30000 = 60000 -> saturates to 32767
    // a2+a3 = -30000-30000 = -60000 -> saturates to -32768
    // b0+b1 = 20000-20000 = 0
    // b2+b3 = 20000-20000 = 0

    ASSERT(32767,  r[0]);
    ASSERT(-32768, r[1]);
    ASSERT(0,      r[2]);
    ASSERT(0,      r[3]);

    printf("OK\n");
    return 0;
}
