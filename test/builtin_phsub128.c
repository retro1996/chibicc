#include "test.h"

typedef short v8hi __attribute__((vector_size(16)));

int main() {
    // Input vectors
    v8hi a = {10, 1, 50, 10, 100, 25, 7, 3};
    v8hi b = {20, 5, 40, 10, 80, 60, 100, 30};

    // phsubw128 performs:
    // [a0 - a1, a2 - a3, a4 - a5, a6 - a7,
    //  b0 - b1, b2 - b3, b4 - b5, b6 - b7]

    v8hi result = __builtin_ia32_phsubw128(a, b);

    // expected:
    // a0-a1 = 10-1 = 9
    // a2-a3 = 50-10 = 40
    // a4-a5 = 100-25 = 75
    // a6-a7 = 7-3 = 4

    // b0-b1 = 20-5 = 15
    // b2-b3 = 40-10 = 30
    // b4-b5 = 80-60 = 20
    // b6-b7 = 100-30 = 70

    short expected[8] = {9, 40, 75, 4, 15, 30, 20, 70};

    for (int i = 0; i < 8; i++) {
        ASSERT(expected[i], result[i]);
    }

    printf("OK\n");
    return 0;
}
