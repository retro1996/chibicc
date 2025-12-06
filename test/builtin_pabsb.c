#include "test.h"

typedef char v8qi __attribute__((vector_size(8)));

int main() {
    v8qi a = {-1, 2, -3, 4, -5, 6, -7, 8};

    v8qi r = __builtin_ia32_pabsb(a);

    int expected[8] = {1,2,3,4,5,6,7,8};

    for(int i=0;i<8;i++)
        ASSERT(expected[i], r[i]);

    printf("PABSB MMX OK\n");
    return 0;
}
