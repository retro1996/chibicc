#include "test.h"
//#include <smmintrin.h>

typedef double v2df __attribute__((vector_size(16)));


int main() {
    v2df X    = { 1.0f,  2.0f };
    v2df Y    = {-1.0f, -2.0f };
    v2df MASK = {-1.0f,  0.0f }; // negative selects Y, zero selects X

    v2df R = __builtin_ia32_blendvpd(X, Y, MASK);

    printf("X    = {%.1f, %.1f}\n",
           X[0], X[1]);
    printf("Y    = {%.1f, %.1f}\n",
           Y[0], Y[1]);
    printf("MASK = {%.1f, %.1f}\n",
           MASK[0], MASK[1]);
    printf("R    = {%.1f, %.1f}\n",
           R[0], R[1]);

    if (R[0] == -1.0f &&
        R[1] ==  2.0f) {
        printf("blendvpd OK\n");
        return 0;
    }

    printf("blendvpd FAIL\n");
    return 1;
}
