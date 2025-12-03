#include "test.h"
#include <stdio.h>

typedef signed char  v16qi __attribute__((vector_size(16)));
typedef short        v8hi  __attribute__((vector_size(16)));

int main() {
    // Unsigned bytes in a, signed bytes in b.
    // pmaddubsw: multiply unsigned a[i] * signed b[i],
    // pairwise add into 16-bit with saturation.

    v16qi a = {
        10, 20,   30, -1,   40, 50,   60, 70,
        80, 90,  100,110,  120,127,  200,255
    };

    v16qi b = {
        1, -2,   3, 4,   -5, 6,   -7, 8,
        -9,10, -11,12, -13,14, -15,16
    };

    v8hi r = __builtin_ia32_pmaddubsw128(a, b);

    // Compute expected results pairwise:
    // r[i] = a[2*i] * b[2*i] + a[2*i+1] * b[2*i+1]

    short exp[8];
    for (int i = 0; i < 8; i++) {
        int t0 = (unsigned char)a[2*i] * (signed char)b[2*i];
        int t1 = (unsigned char)a[2*i+1] * (signed char)b[2*i+1];
        int sum = t0 + t1;
        if (sum > 32767) sum = 32767;
        if (sum < -32768) sum = -32768;
        exp[i] = sum;
    }

    for (int i = 0; i < 8; i++) {
        ASSERT(exp[i], r[i]);
    }

    printf("pmaddubsw128 OK\n");
    return 0;
}
