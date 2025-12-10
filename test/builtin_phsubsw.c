#include "test.h"
#include <stdio.h>

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = { 30000, -30000, 20000, -20000 };
    v4hi b = { -10000, 10000, -20000, 20000 };

    v4hi r = __builtin_ia32_phsubsw(a, b);

    // Saturating subtraction:
    // 30000 - (-30000) = 32767
    // 20000 - (-20000) = 32767
    // -10000 - 10000   = -20000
    // -20000 - 20000   = -32768

    ASSERT(32767,  r[0]);
    ASSERT(32767,  r[1]);
    ASSERT(-20000, r[2]);
    ASSERT(-32768, r[3]);

    printf("phsubsw OK\n");
    return 0;
}
