#include "test.h"


typedef char v16qi __attribute__((vector_size(16)));

v16qi f(v16qi x, v16qi y) {
    return __builtin_ia32_pminsb128(x, y);
}

int main() {
    v16qi X = {1, -5, 20, -30, 7, 8, -9, 10,  30, -40, 50, -60, 70, -80, 90, -100};
    v16qi Y = {2, -10,15, -25, 9,-12, -3, 40, -31, -5, 60, -70, 60, -90, 95, -90};

    v16qi R = f(X, Y);

    printf("R = {");
    for (int i=0;i<16;i++) printf("%d%s", R[i], i<15?", ":"");
    printf("}\n");

    // Expected signed byte-wise min
    char expect[16];
    for (int i=0;i<16;i++)
        expect[i] = X[i] < Y[i] ? X[i] : Y[i];

    int ok = 1;
    for (int i=0;i<16;i++)
        if (R[i] != expect[i]) ok = 0;

    printf("pminsb128 %s\n", ok ? "OK" : "FAIL");
    return 0;
}
