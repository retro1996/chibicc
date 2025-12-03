#include "test.h"
#include <stdio.h>

typedef unsigned char v8qi  __attribute__((vector_size(8)));   // MMX args
typedef short         v4hi  __attribute__((vector_size(8)));   // MMX result

int main() {
    // pmaddubsw operates pairwise:
    // (a0 * b0) + (a1 * b1), saturating to int16_t

    v8qi a = { 1, 2,  3, 4,   5, 6,  7, 8 };
    v8qi b = {10,20, 30,40,  50,60, 70,80 };

    v4hi r = __builtin_ia32_pmaddubsw(a, b);

    // expected:
    // (1*10 + 2*20) = 10 + 40  = 50
    // (3*30 + 4*40) = 90 +160  = 250
    // (5*50 + 6*60) = 250+360  = 610
    // (7*70 + 8*80) = 490+640  = 1130

    ASSERT(50,   r[0]);
    ASSERT(250,  r[1]);
    ASSERT(610,  r[2]);
    ASSERT(1130, r[3]);

    printf("pmaddubsw (MMX) OK\n");
    return 0;
}
