#include "test.h"

typedef char v16qi __attribute__((vector_size(16)));

v16qi test_max(v16qi x, v16qi y) {
    return __builtin_ia32_pmaxsb128(x, y);
}

int main() {
    v16qi X = {  1, -2,  3, -4,  5, -6,  7, -8, 100, -100, 50, -50, 1, 2, 3, 4 };
    v16qi Y = { -1,  2, -3,  4, -5,  6, -7,  8, -90, -200, 60, -60, 0, 3, 5, 2 };

    v16qi R = test_max(X, Y);

    printf("X = {");
    for (int i=0;i<16;i++) printf("%d%s", X[i], i==15?"} \n":", ");
    printf("Y = {");
    for (int i=0;i<16;i++) printf("%d%s", Y[i], i==15?"} \n":", ");
    printf("R = {");
    for (int i=0;i<16;i++) printf("%d%s", R[i], i==15?"} \n":", ");

    // Expected element-wise signed max
    int ok = 1;
    for (int i=0;i<16;i++) {
        signed char e = X[i] > Y[i] ? X[i] : Y[i];
        if (R[i] != e) ok = 0;
    }

    printf("pmaxsb128 %s\n", ok ? "OK" : "FAIL");
    return ok ? 0 : 1;
}
