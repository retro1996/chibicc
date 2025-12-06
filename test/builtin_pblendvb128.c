#include "test.h"
//#include <smmintrin.h>


typedef char  v16qi __attribute__((vector_size(16)));

static void dump(const char *name, v16qi v) {
    printf("%s = {", name);
    for (int i = 0; i < 16; i++) {
        printf("%d", v[i]);
        if (i != 15) printf(", ");
    }
    printf("}\n");
}

int main(void) {
    // X: all positive
    v16qi X = {  1,  2,  3,  4,  5,  6,  7,  8,
                 9, 10, 11, 12, 13, 14, 15, 16 };

    // Y: all negative
    v16qi Y = { -1, -2, -3, -4, -5, -6, -7, -8,
                -9,-10,-11,-12,-13,-14,-15,-16 };

    // Mask: select lower 8 bytes from Y (MSB=1) and upper 8 from X (MSB=0)
    v16qi MASK = {
        (signed char)0x80, (signed char)0x80, (signed char)0x80, (signed char)0x80,
        (signed char)0x80, (signed char)0x80, (signed char)0x80, (signed char)0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    v16qi R = (v16qi)__builtin_ia32_pblendvb128(
        (v16qi)X,   // X
        (v16qi)Y,   // Y
        (v16qi)MASK // Mask (MSB decides)
    );

    dump("X", X);
    dump("Y", Y);
    dump("MASK", MASK);
    dump("R", R);

    // Expected:
    // R = { Y[0..7], X[8..15] }
    int ok = 1;
    for (int i = 0; i < 8; i++)
        if (R[i] != Y[i]) ok = 0;

    for (int i = 8; i < 16; i++)
        if (R[i] != X[i]) ok = 0;

    printf(ok ? "pblendvb128 OK\n" : "pblendvb128 FAIL\n");
    return ok ? 0 : 1;
}