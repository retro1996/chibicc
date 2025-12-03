#include "test.h"
#include <stdio.h>

typedef signed char v8qi __attribute__((vector_size(8)));

int main() {
    // source bytes
    v8qi x = {10, 20, 30, 40, 50, 60, 70, 80};

    // shuffle mask: take elements in reverse order
    v8qi mask = {7, 6, 5, 4, 3, 2, 1, 0};

    v8qi r = __builtin_ia32_pshufb(x, mask);

    ASSERT(80, r[0]);
    ASSERT(70, r[1]);
    ASSERT(60, r[2]);
    ASSERT(50, r[3]);
    ASSERT(40, r[4]);
    ASSERT(30, r[5]);
    ASSERT(20, r[6]);
    ASSERT(10, r[7]);

    printf("pshufb64 OK\n");
}
