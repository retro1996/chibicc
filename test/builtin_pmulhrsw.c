#include "test.h"
#include <stdio.h>

typedef short v4hi __attribute__((vector_size(8)));

static short pmulhrsw_ref(short a, short b) {
    int prod = (int)a * (int)b;
    prod += 0x4000;       // rounding bias
    prod >>= 15;
    if (prod > 32767) prod = 32767;
    if (prod < -32768) prod = -32768;
    return (short)prod;
}

int main() {
    v4hi a = { 1000, -2000, 3000, -4000 };
    v4hi b = { 2, -3, 4, -5 };

    v4hi r = __builtin_ia32_pmulhrsw(a, b);

    ASSERT(pmulhrsw_ref(a[0], b[0]), r[0]);
    ASSERT(pmulhrsw_ref(a[1], b[1]), r[1]);
    ASSERT(pmulhrsw_ref(a[2], b[2]), r[2]);
    ASSERT(pmulhrsw_ref(a[3], b[3]), r[3]);

    printf("pmulhrsw (MMX) OK\n");
    return 0;
}
