#include "test.h"


typedef char v16qi __attribute__((vector_size(16)));

int main() {
    v16qi a = {-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15, 16};

    v16qi r = __builtin_ia32_pabsb128(a);

    int expected[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

    for (int i=0;i<16;i++)
        ASSERT(expected[i], r[i]);

    printf("PABSB128 OK\n");
    return 0;
}
