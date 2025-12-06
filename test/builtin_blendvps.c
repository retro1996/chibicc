#include "test.h"
//#include <smmintrin.h>

typedef float v4sf __attribute__((vector_size(16)));


int main() {
    v4sf X    = { 1.0f,  2.0f,  3.0f,  4.0f };
    v4sf Y    = {-1.0f, -2.0f, -3.0f, -4.0f };
    v4sf MASK = {-1.0f,  0.0f, -1.0f,  0.0f }; // negative selects Y, zero selects X

    v4sf R = __builtin_ia32_blendvps(X, Y, MASK);

    printf("X    = {%.1f, %.1f, %.1f, %.1f}\n",
           X[0], X[1], X[2], X[3]);
    printf("Y    = {%.1f, %.1f, %.1f, %.1f}\n",
           Y[0], Y[1], Y[2], Y[3]);
    printf("MASK = {%.1f, %.1f, %.1f, %.1f}\n",
           MASK[0], MASK[1], MASK[2], MASK[3]);
    printf("R    = {%.1f, %.1f, %.1f, %.1f}\n",
           R[0], R[1], R[2], R[3]);

    if (R[0] == -1.0f &&
        R[1] ==  2.0f &&
        R[2] == -3.0f &&
        R[3] ==  4.0f) {
        printf("blendvps OK\n");
        return 0;
    }

    printf("blendvps FAIL\n");
    return 1;
}
